/*
 ╔═════════════════════════[ХХХ]═════════════════════════════╗
 ║   Name        : calculator_3.c                            ║
 ║   Author      : Darya K  (https://github.com/Grief3749)   ║
 ║   Version     : 3.1                                       ║
 ║   Copyright   : all rights reserved                       ║
 ║   Description : calculator of numbers and vectors in C    ║
 ╚═══════════════════════════════════════════════════════════╝
 */

/*
╔═══════════════════════════════[DESCRIPTION]════════════════════════════════╗
║  the calculator program performs 6 operations with two numbers as well     ║
║  as operations with vectors                                                ║
║                                                                            ║
║  MANUAL: at the beginning, the calculator prompts the user to choose       ║
║  whether he wants to work with numbers or vectors                          ║
║  further, in accordance with the selected block, the program displays      ║
║  a list of available operations                                            ║
║                                                                            ║
║  if the user has chosen to work with numbers, the program requests the     ║
║  first number, then the operation,                                         ║
║  and depending on the operation, requests the second number, if necessary  ║
║                                                                            ║
║  if the user has chosen to work with vectors, the program requests an      ║
║  operation, and then two vectors                                           ║
║                                                                            ║
║  the calculator performs actions and outputs the result                    ║
║                                                                            ║
║  WARNING: if you enter something not according to the instructions,        ║
║  the program will give an error                                            ║
╚════════════════════════════════════════════════════════════════════════════╝
 */

//operations:
//+ - addition
//- - subtraction
//* - multiplication
/// - division
//! - factorial
//^ - exponentiation


// s - vector summation
// p - scalar product
// r - vector difference


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);

char op, opv, rep, answer;
int deg;
float var1, var2, zdeg;
long long int fac;
float *v1, *v2, *result, res;
int size;

/*printf("numerical operations are available:\n");
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
printf("r - vector difference\n");
 */


printf("will you work with vectors or numbers? (if with vectors write v, if with numbers write с)\n ");
scanf(" %s", &answer);


do //continuation of the cycle "while"
	{
	if(answer == 'c')
	{
		printf(" ");
		printf("numerical operations are available:\n");
		printf("+ - addition\n");
		printf("- - subtraction\n");
		printf("* - multiplication\n");
		printf("/ - division\n");
		printf("! - factorial\n");
		printf("^ - exponentiation\n");
		printf(" ");

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

		printf("vector operations:\n");
		printf("s - vector summation\n");
		printf("p - scalar product\n");
		printf("r - vector difference\n");

		printf("enter the operation (s, r, p): \n");
		scanf(" %c", &opv); //scans the operation
		printf("enter the size of the vectors: ");
		scanf("%i", &size);
		v1 = malloc(size*sizeof(int)); //sets arrays
		v2 = malloc(size*sizeof(int));
		result = malloc(size*sizeof(int));
		printf("enter first vector: \n");
		for(int i=0; i < size; i++) //scans the first vector
		{
			printf("enter %i coordinate: \n", i + 1);
			scanf("%f", &v1[i]);
		}
		printf("enter second vector: \n"); //scans the second vector
		for(int i=0; i < size; i++)
		{
			printf("enter %i coordinate: \n", i + 1);
			scanf("%f", &v2[i]);
		}

		if(opv == 's')
		{
			printf("result of vector addition: \n");
			for(int i=0; i < size; i++)
				printf("%f ", v1[i] + v2[i]);
			printf("\n");
		}

		if(opv == 'r')
		{
			printf("result of vector difference: \n");
			for(int i=0; i < size; i++)
				printf("%f ", v1[i] - v2[i]);
			printf("\n");
		}

		if(opv == 'p')
		{
			printf("result of scalar product: \n");
			for(int i=0; i < size; i++)
			{

				res +=  v1[i]*v2[i];

			printf("\n");
			}
		printf("%f ", res);
		res = 0;
		}

		free(v1);
		free(v2);
		free(result);



	}




	printf("do you want to continue? (write y if yes, or n if no)\n ");
	scanf(" %s", &rep); //reads the response
	}
while(rep == 'y'); //start of the cycle

printf("thank you for your cooperation!");

return 0;

}
