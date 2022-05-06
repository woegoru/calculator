/*
 ╔═════════════════════════[ХХХ]═════════════════════════════╗
 ║   Name        : calculator_3.c                            ║
 ║   Author      : Darya K  (https://github.com/Grief3749)   ║
 ║   Version     : 5.2                                       ║
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


#include <stdio.h>
#include <stdlib.h>

struct inital_data{
	char op, mode;
	int size;
	float *data;
};

typedef struct main_list{
	struct inital_data data;
	struct main_list *next, *previous, *head, *tail;
}list;

list* new_list(struct inital_data, inital_data){
	list* new_list = malloc(sizeof(list));
	new_list->data = inital_data;
	new_list->next = NULL;
	return new_list;
}

void addfirst(list **headlist, struct inital_data inital_data){
	list* extlist = *headlist;
	list* newelement = new_list(inital_data);
	newelement->data = inital_data;
	newelement->head = newelement;
	newelement->next = extlist;
	extlist->previous = newelement;
	while(newelement->next != NULL){
		newelement = newelement->next;
		newelement->head = newelement->previous->head;
	}
	newelement = newelement->head;
	*headlist = newelement;
}

void addlast(list **headlist, struct inital_data inital_data){
	list* extlist = *headlist;
	list* newelement = newContainer();
	newelement->data = inital_data;
	while(extlist->next != NULL){
		extlist = extlist->next;
	}
	newelement->previous = extlist;
	extlist->next = newelement;
	newelement->head = extlist->head;
	newelement = newelement->head;
	*headlist = newelement;
}

void addtolist(list **headlist, struct inital_data inital_data, int number){
	list* extlist = *headlist;
	list* newelement = newContainer();
	int counter = 0;
	if(is_empty(&extlist) == 0){
		extlist->data = inital_data;
		extlist->head = extlist;
	}
	else if(number == -1){
		addfirst(&extlist, inital_data);
	}
	else if(number == elementcounter(&extlist) - 1){
		addlast(&extlist, inital_data);
	}
	else{
		while(number != counter){
			counter++;
			extlist = extlist->next;
		}
		newelement->data = inital_data;
		newelement->previous = extlist;
		newelement->next = extlist->next;
		extlist->next->previous = newelement;
		extlist->next = newelement;
		newelement->head = extlist->head;
		extlist = extlist->head;
	}
	*headlist = extlist;

}

int main(int argc, char *argv[])
{
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);

char rep = 'n';
do
{
{
	//working with a file
	FILE *input, *output;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");

	struct inital_data elem;
	list *inital_data = new_list(elem);

	//declaring variables
	//char op, data;
	//int deg;
	//float var1, var2, zdeg;
	//long long int fac;
	//float *v1, *v2, *result;
	//int size;

	while(feof(input) == 0)
	{
		fscanf(input, " %c", &elem.op);
		fscanf(input, " %c", &elem.mode);

		//working with numbers
		/*if(data == 's')
		{
			fscanf(input, "%f", &var1);
			if (op == '^' || op == '!')
			{
				switch(op)
				{
				case '^': //exponentiation of a number
					zdeg = 1;
					fscanf(input, "%i", &deg);
					if (deg == 0) fprintf(output,"%f^%i = 1\n", var1, deg);
					else if (deg > 0)
						{
						for(int i = 1; i <= deg; i++)
							zdeg = zdeg * var1;
						fprintf(output,"%f^%i = %f\n", var1, deg, zdeg);
						}
					break;
				case '!': //finding the factorial
					fac = 1;
					if (var1 < 0) fprintf(output, "error");
					else if (var1 == 0) fprintf(output, "%f! = 1\n", var1);
					else
						{
						for(int i = 1; i <= var1; i++)
							fac = fac*i;
						fprintf(output, "%f! = %I64i\n", var1, fac);
						}
					break;
				default:
					fprintf(output, "error\n");
					break;
				}
			}
			else
				{

				fscanf(input, "%f", &var2);
				switch(op)
				{
				case '+': //addition operation
					fprintf(output, "%f+%f = %f\n" , var1, var2, var1+var2);
					break;
				case '-': //difference
					fprintf(output, "%f-%f = %f\n" , var1, var2, var1-var2);
					break;
				case '*': //multiplication operation
					fprintf(output, "%f*%f = %f\n" , var1, var2, var1*var2);
					break;
				case '/': //division operation
					fprintf(output, "%f/%f = %f\n" , var1, var2, var1/var2);
					break;
				default:
					fprintf(output, "error\n");
					break;
				}
				}
		}
		*/
		if(elem.mode == 'v') //working with vectors
		{
			//setvbuf(stdout, NULL, _IONBF, 0);
			//setvbuf(stderr, NULL, _IONBF, 0);
			fscanf(input, "%i", &elem.size);
			elem.data = malloc(elem.size*sizeof(double));
			//v1 = malloc(size*sizeof(int)); //the first vector is set
			//v2 = malloc(size*sizeof(int)); //the second vector is set
			//result = malloc(size*sizeof(int));
			//fprintf(output,"("); //entering vectors
			for(int i=0; i < elem.size*2; i++)
			{
				fscanf(input, "%f", &elem.data[i]);
				//fprintf(output, " %f", v1[i]);
			}
			//fprintf(output," ) ");
			addlast(&inital_data, elem);
		}
		else if(elem.mode == 's')
		{
			if(elem.op == '!')
			{
				elem.data = malloc(sizeof(double));
				fscanf(input, "%f", &elem.data[0]);
			}
			else
			{
				elem.data = malloc(sizeof(double)*2);
				fscanf(input, "%f", &elem.data[0]);
				fscanf(input, "%f", &elem.data[1]);
			}
			addlast(&inital_data, elem);
		}
	}

			fprintf(output,"%c", op);
			fprintf(output," (");
			for(int i=0; i < size; i++)
			{
				fscanf(input, "%f", &v2[i]);
				fprintf(output, " %f", v2[i]);
			}
			fprintf(output," ) = ");

			if(op == '+') //addition operation
			{
				fprintf(output, "( ");
				for(int i=0; i < size; i++)
				{
					result[i] = v1[i] + v2[i];
					fprintf(output,"%f ", result[i]);
				}
				fprintf(output, ")\n");
			}

			if(op == '-') //difference
			{
				fprintf(output, "( ");
				for(int i=0; i < size; i++)
				{
					result[i] = v1[i] - v2[i];
					fprintf(output,"%f ", result[i]);
				}
				fprintf(output, ")\n");
			}

			if(op == '*') //multiplication operation
			{
				fprintf(output, "( ");
				for(int i=0; i < size; i++)
				{
					result[i] = v1[i] * v2[i];
					fprintf(output,"%f ", result[i]);
				}
				fprintf(output, ")\n");
			}

			free(v1);
			free(v2);
			free(result);
	}
	}
	fclose(input);
	fclose(output);
}

	}
	while(rep == 'y');
	return 0;

}
