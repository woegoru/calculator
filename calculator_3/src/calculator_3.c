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


// s - vector summation
// p - scalar product
// r - vector product
// m - multiplication of a vector by a number

#include <stdio.h>
int main(int argc, char *argv[])
{
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);

char op, opv, rep, answer;
int deg;
float var1, var2, zdeg, number;
long long int fac;
double x1, x2, y1, y2, z1, z2;

printf("numerical operations are available:\n");
printf("+ - addition\n");
printf("- - subtraction\n");
printf("* - multiplication\n");
printf("/ - division\n");
printf("! - factorial\n");
printf("^ - exponentiation\n");
printf(" ");
printf("vector operations:\n");
printf("s - vector summation\n");
printf("p - scalar product\n");
printf("r - vector product\n");
printf("m - multiplication of a vector by a number\n");


printf("will you work with vectors or numbers? (if with vectors write v, if with numbers write с)\n ");
scanf(" %s", &answer);


do //continuation of the cycle "while"
	{
	if(answer == 'c')
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
	}
	if(answer == 'v')
		{
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);
		printf("enter the operation (s, p,  r,  m): ");
		scanf(" %c", &opv); //scans the operation

		printf("enter the coordinates of the first vector\n"); //scans the coordinates of the first vector
		printf("x1: ");
		scanf("%lf", &x1);
		printf("y1: ");
		scanf("%lf", &y1);
		printf("z1: ");
		scanf("%lf", &z1);

		if (opv == 'm')
		{
			printf("enter the number by which we will multiply:\n");
			scanf("%f", &number);
			printf("%lf*%f, %lf*%f, %lf*%f = %lf,%lf,%lf\n" ,x1, number, y1,number, z1, number, x1*number, y1*number, z1*number);
		} //multiplying a vector by a number

		if (opv != 'm')
		{
			printf("enter the coordinates of the second vector\n"); //scans the coordinates of the second vector
			printf("x2: ");
			scanf("%lf", &x2);
			printf("y2: ");
			scanf("%lf", &y2);
			printf("z2: ");
			scanf("%lf", &z2);

			switch(opv)
			{
			case 's':
				printf("%lf+%lf,%lf+%lf, %lf+%lf = %lf,%lf,%lf\n" ,x1,x2,y1,y2,z1,z2, x1+x2, y1+y2, z1+z2); //addition of vectors
				break;
			case 'p':
				printf("%lf*%lf+%lf*%lf+%lf*%lf = %lf\n" ,x1,x2,y1,y2,z1,z2, x1*x2+y1*y2+z1*z2); //scalar product
				break;
				//        | i   j  k |
				//[a,b] = | x1 y1 z1 | = i(y1*z2-y2*z1) - j(x1*z2-x2*z1) +k(x1*y2-x2*y1)=(x3,y3,z3)
				//        | x2 y2 z2 |
			case 'r':
				printf("%lf*%lf-%lf*%lf,%lf*%lf-%lf*%lf,%lf*%lf-%lf*%lf = %lf,%lf,%lf\n", y1,z2,y2,z1,x1,z2,x2,z1,x1,y2,x2,y1, (y1*z2-y2*z1),-(x1*z2-x2*z1),(x1*y2-x2*y1)); //scalar product
				break; //vector product
			default:
				printf("error\n");
				break;
			}
		}

		}
	else printf("error\n");


	printf("do you want to continue? (write y if yes, or n if no)\n ");
	scanf(" %s", &rep); //reads the response
	}
while(rep == 'y'); //start of the cycle

printf("thank you for your cooperation!");

return 0;

}
