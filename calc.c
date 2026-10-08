#include <stdio.h>

int main(void)
{
	double first, second;
	char operation;

	printf("Enter an operation (+, -, *, /): ");
	if (scanf(" %c", &operation) != 1) {
		printf("Invalid input.\n");
		return 1;
	}

	printf("Enter two numbers: ");
	if (scanf("%lf %lf", &first, &second) != 2) {
		printf("Invalid input.\n");
		return 1;
	}

	switch (operation) {
	case '+':
		printf("Result: %g\n", first + second);
		break;
	case '-':
		printf("Result: %g\n", first - second);
		break;
	case '*':
		printf("Result: %g\n", first * second);
		break;
	case '/':
		if (second == 0) {
			printf("Error: division by zero.\n");
			return 1;
		}
		printf("Result: %g\n", first / second);
		break;
	default:
		printf("Invalid operation.\n");
		return 1;
	}

	return 0;
}
