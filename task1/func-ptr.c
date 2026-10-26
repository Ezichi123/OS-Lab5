#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "util.h"

#define DEBUG 0			//change this to 1 to enable verbose output

/**
 * Signature for a function pointer that can compare
 * You need to cast the input into its actual
 * type and then compare them according to your
 * custom logic
 */
typedef int (*Comparer) (const void *a, const void *b);

/**
 * compares 2 processes
 * You can assume:
 * - Process ids will be unique
 * - No 2 processes will have same arrival time
 *
 * Sort order:
 * - Higher priority number comes first (descending)
 * - On equal priority, earlier arrival time comes first (ascending)
 */
int my_comparer(const void *this, const void *that)
{
	const Process *p1 = (const Process *) this;
	const Process *p2 = (const Process *) that;

	int p1_priority = p1->priority;
	int p2_priority = p2->priority;

	/* Different priorities: higher priority number goes first */
	if (p1_priority != p2_priority) {
		int priority_diff = p2_priority - p1_priority;
		return priority_diff;
	}

	int p1_arrival = p1->arrival_time;
	int p2_arrival = p2->arrival_time;

	/* Same priority: smaller arrival time goes first */
	int arrival_diff = p1_arrival - p2_arrival;
	return arrival_diff;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
		fflush(stderr);
		return 1;
	}

	/*******************/
	/* Parse the input */
	/*******************/
	FILE *input_file = fopen(argv[1], "r");
	if (!input_file) {
		fprintf(stderr, "Error: Invalid filepath\n");
		fflush(stderr);
		return 1;
	}

	Process *processes = parse_file(input_file);

	/*******************/
	/* sort the input  */
	/*******************/
	Comparer process_comparer = &my_comparer;

#if DEBUG
	for (int i = 0; i < P_SIZE; i++) {
		printf("%d (%d, %d) ",
		       processes[i].pid,
		       processes[i].priority,
		       processes[i].arrival_time);
	}
	printf("\n");
#endif

	qsort(processes, P_SIZE, sizeof(Process), process_comparer);

	/**************************/
	/* print the sorted data  */
	/**************************/
	for (int i = 0; i < P_SIZE; i++) {
		printf("%d (%d, %d)\n",
		       processes[i].pid,
		       processes[i].priority,
		       processes[i].arrival_time);
	}
	fflush(stdout);
	fflush(stderr);

	/************/
	/* clean up */
	/************/
	free(processes);
	fclose(input_file);
	return 0;
}