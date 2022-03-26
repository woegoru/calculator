/*
 ============================================================================
 Name        : calculator_3.c
 Author      : Darya K
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//the calculator program performs 6 operations with two numbers

//manual: at the beginning, the calculator displays a list of available operations
//two numbers are entered from the keyboard and the operation to be performed on these numbers.
//the calculator performs actions with numbers and outputs the answer

//operations:
//+ - addition
//- - subtraction
//* - multiplication
/// - division
//! - factorial
//^ - exponentiation

#include <stdio.h>
int main(int argc, char *argv[])
{
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);

char op, rep;
int deg;
float var1, var2, zdeg;
long long int fac;

printf("operations are available:\n");
printf("+ - addition\n");
printf("- - subtraction\n");
printf("* - multiplication\n");
printf("/ - division\n");
printf("! - factorial\n");
printf("^ - exponentiation\n");

do //continuation of the cycle "while"
	{
	printf("enter the first number: ");
	scanf("%f", &var1); //scans the first number
	printf("enter the operation (+,-,/,*,^,!): ");
	scanf(" %c", &op); //scans the operation
	if (op == '^' || op == '!')
	{
		switch(op) //if the degree of a number or a factorial, then the second variable is not needed
		{
		case '^':
			zdeg = 1; //the result of exponentiation is stored here
			printf("enter the degree of the number: ");
			scanf("%i", &deg);//reads the power of a number
			if (deg == 0) printf("%f^%i = 1\n", var1, deg); //if the degree is 0
			else if (deg > 0) //if the degree is greater than 0
				{
				for(int i = 1; i <= deg; i++)
					zdeg = zdeg * var1;
				printf("%f^%i = %f\n", var1, deg, zdeg);
				}
			break;
		case '!': //factorial of a number
			fac = 1; //the result of the factorial is stored here
			if (var1 < 0) printf("error"); //the factorial of negative numbers does not exist
			else if (var1 == 0) printf("%f! = 1\n", var1);
			else
				{
				for(int i = 1; i <= var1; i++)
					fac = fac*i;
				printf("%f! = %I64i\n", var1, fac);
				}
			break;
		default:
			printf("error\n");
			break;
		}
	}
	else
		{
		printf("enter the second number: ");
		scanf("%f", &var2); //scans the second number
		switch(op)
		{

		case '+':
			printf("%f+%f = %f\n" , var1, var2, var1+var2); //addition operation
			break;
		case '-':
			printf("%f-%f = %f\n" , var1, var2, var1-var2); //subtraction operation
			break;
		case '*':
			printf("%f*%f = %f\n" , var1, var2, var1*var2); //multiplication operation
			break;
		case '/':
			printf("%f/%f = %f\n" , var1, var2, var1/var2); //division operation
			break;
		default:
			printf("error\n");
			break;
		}
		}

	printf("do you want to continue? (write y if yes, or n if no)\n ");
	scanf(" %s", &rep); //reads the response
	}
while(rep == 'y'); //start of the cycle

printf("thank you for your cooperation!");

return 0;

}
