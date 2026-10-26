#include <stdio.h>
#include <stdlib.h>

/* Function declarations */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int exit_program(int a, int b);

int main(void)
{
	int a = 6;
	int b = 3;
	char choice;

	/* Array of function pointers, indexed by the user's choice */
	int (*operations[5])(int, int) = {add, subtract, multiply, divide, exit_program};

	printf("Operand 'a' : %d | Operand 'b' : %d\n", a, b);
	printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit): ");
	scanf(" %c", &choice);

	/*
	 * Convert the character '0'-'4' into the number 0-4.
	 * Only inputs 0-4 are valid. Any other character would index
	 * outside the operations array (undefined behavior). Input is not
	 * validated because the assignment forbids conditional statements.
	 */
	int index = choice - '0';

	/* Pick the matching function and call it */
	int (*selected)(int, int) = operations[index];
	int x = selected(a, b);

	printf("x = %d\n", x);

	return 0;
}

/* Function definitions */

/* Returns a + b */
int add(int a, int b)
{
	printf("Adding 'a' and 'b'\n");
	int result = a + b;
	return result;
}

/* Returns a - b */
int subtract(int a, int b)
{
	printf("Subtracting 'b' from 'a'\n");
	int result = a - b;
	return result;
}

/* Returns a * b (integer multiplication) */
int multiply(int a, int b)
{
	printf("Multiplying 'a' and 'b'\n");
	int result = a * b;
	return result;
}

/* Returns a / b (integer division, remainder discarded) */
int divide(int a, int b)
{
	printf("Dividing 'a' by 'b'\n");
	int result = a / b;
	return result;
}

/* Ends the program. Takes (int, int) only so it fits in the operations array */
int exit_program(int a, int b)
{
	exit(0);
}