/*
 ╔═════════════════════════[ХХХ]═════════════════════════════╗
 ║   Name        : calculator_3.c                            ║
 ║   Author      : Darya K  (https://github.com/Grief3749)   ║
 ║   Version     : 6.8                                       ║
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

//adding queue from a prepared file

//basic data structure
struct inital_data
{
	char op, mode;
	int size;
	float *data;
};

//creating a new type
typedef struct elem
{
	struct inital_data inital_data;
	struct elem *next, *previous, *head, *tail;
}queue;

//creating new queue
queue* new_queue()
{
	queue* new_queue = malloc(sizeof(queue));
	new_queue->next = NULL;
	new_queue->previous = NULL;
	new_queue->head = NULL;
	new_queue->tail = NULL;
	return new_queue;
}
int is_empty(queue **headqueue)
{
	queue *extelem = *headqueue;
	if(extelem->head == NULL)
	{
		return 0;
	}
	else return 1;
}

int elemcounter(queue **headqueue)
{
	queue* extelem = new_queue();
	extelem = *headqueue;
	int counter = 0;
	if(is_empty(&extelem) == 0)
	{
		return counter;
	}
	else{
		while(extelem != NULL)
		{
			counter = counter + 1;
			extelem = extelem->next;
		}
		return counter;
	}
}

void addqueue(queue **headcont, struct inital_data inital_data)
{
	queue* extelem = new_queue();
	queue* addelem = new_queue();
	extelem = *headcont;
	if(elemcounter(&extelem) == 0)
	{
        addelem->inital_data = inital_data;
        addelem->head = addelem;
        addelem->tail = addelem;
        extelem = addelem;
	}
	else
	{
		addelem->inital_data = inital_data;
		addelem->head = addelem;
		addelem->next = addelem;
		addelem->tail = extelem->tail;
		extelem->previous = addelem;
		while (extelem != NULL)
		{
			extelem->head = addelem;
			extelem = extelem->next;
		}
	extelem = addelem;
	}
	*headcont = extelem;
}

struct inital_data find(queue **headcont)
{
	queue* extfind = *headcont;
	struct inital_data find_data;
	if(elemcounter(&extfind) > 1)
	{
		find_data = extfind->tail->inital_data;
		extfind = extfind->tail->previous;
		extfind->tail = extfind;
		extfind->next = NULL;
		while(extfind->previous != NULL)
		{
			extfind = extfind->previous;
			extfind->tail = extfind->next->tail;
		}
	extfind = extfind->head;
	extfind->tail = extfind->next->tail;
	}

	else if(elemcounter(&extfind) == 1)
	{
		find_data = extfind->inital_data;
		extfind->next = NULL;
		extfind->head = NULL;
		extfind->previous = NULL;
		extfind->tail = NULL;
	}
	return find_data;
}


//the main part
int main(int argc, char *argv[])
{
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);

char rep = 'n';
do
{
	//working with a file
	FILE *input, *output;
	input = fopen("input.txt", "r");


	struct inital_data elem;
	queue *inital_data = new_queue();

	int deg, fac; //auxiliary variables for calculation

	//reading a file
	while(feof(input) == 0)
	{
		fscanf(input, " %c", &elem.op);
		fscanf(input, " %c", &elem.mode);
		if(elem.mode == 's')
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
		}
		else if(elem.mode == 'v')
		{
			fscanf(input, "%i", &elem.size);
			elem.data = malloc(elem.size*sizeof(double));
			for(int i=0; i < elem.size*2; i++)
			{
				fscanf(input, "%f", &elem.data[i]);
			}
		}
		addqueue(&inital_data, elem);
	}

	//closing a file
	fclose(input);

	struct inital_data inital_link, deducting_link;
	struct inital_data deducting_elem;

	inital_link.data = malloc(inital_data->inital_data.size*sizeof(double));
	deducting_link.data = malloc(inital_data->inital_data.size*sizeof(double));
	deducting_elem.data = malloc(inital_data->inital_data.size*sizeof(double));

	queue* deducting_list = new_queue();
	queue* deducting_cont_op = new_queue();

	while(is_empty(&inital_data) != 0)
	{
		inital_link = find(&inital_data);
		addqueue(&deducting_cont_op, inital_link);
		deducting_elem.data = malloc(inital_data->inital_data.size*sizeof(double));
		if(inital_link.mode == 'v') //working with vectors
		{
			switch(inital_link.op)
		{
				case '+':
					for(int i=0; i < inital_link.size; i++) //addition
					{
						deducting_elem.data[i] = inital_link.data[i] + inital_link.data[inital_link.size+i];
					}
					break;
				case '-':
					for(int i=0; i < inital_link.size; i++) //addition
					{
						deducting_elem.data[i] = inital_link.data[i] - inital_link.data[inital_link.size+i];
					}
					break;
				case '*':
					for(int i=0; i < inital_link.size; i++) //addition
					{
						deducting_elem.data[i] = inital_link.data[i] * inital_link.data[inital_link.size+i];
					}
					break;
				case '/':
					for(int i=0; i < inital_link.size; i++) //addition
					{
						deducting_elem.data[i] = inital_link.data[i] / inital_link.data[inital_link.size+i];
					}
					break;
				default:
					deducting_elem.op = 'E';
					break;
		}
		}
		else if(inital_link.mode == 's') //working with numbers
		{
			if(inital_link.op == '!' || inital_link.op == '^')
			{
				switch(inital_link.op)
				{
				case '!': //finding the factorial
					fac = 1;
					if(inital_link.data[0] == 0)
					{
						deducting_elem.data[0] = 1;
					}
					if(inital_link.data[0] > 0)
					{
						for(int i=1; i <= inital_link.data[0]; i++)
						{
							fac = i * fac;
						}
						deducting_elem.data[0] = fac;
					}
					else
					{
						deducting_elem.op = 'E';
					}
					break;
				case '^': //exponentiation
					deg = 1;
					if(inital_link.data[0] == 0)
					{
						deducting_elem.data[0] = 1;
					}
					if(inital_link.data[1] > 0)
					{
						for(int i=1; i <= inital_link.data[1]; i++)
						{
							deg = deg * inital_link.data[0];
						}
						deducting_elem.data[0] = deg;
					}
					if(inital_link.data[1] < 0)
					{
						for(int i=1; i <= inital_link.data[1]; i++)
						{
							deg = deg / inital_link.data[0];
						}
						deducting_elem.data[0] = deg;
					}
					break;
				default:
					deducting_elem.op = 'E';
					break;
				}
			}
			else
			{
				switch(inital_link.op)
				{
				case '+': //addition
					deducting_elem.data[0] = inital_link.data[0] + inital_link.data[1];
					break;
				case '-': //subtraction
					deducting_elem.data[0] = inital_link.data[0] - inital_link.data[1];
					break;
				case '*': //multiplication
					deducting_elem.data[0] = inital_link.data[0] * inital_link.data[1];
					break;
				case '/': //division
					deducting_elem.data[0] = inital_link.data[0] / inital_link.data[1];
					break;
				default:
					deducting_elem.op = 'E';
					break;

				}
			}
		}
		else
		{
			deducting_elem.op = 'E';
		}
		addqueue(&deducting_list, deducting_elem);
	}
	output = fopen("output.txt", "w");

	//working with output
	while(is_empty(&deducting_list) != 0)
	{
		inital_link = find(&deducting_cont_op);
		deducting_link = find(&deducting_list);
		if(deducting_link.op == 'E')
		{
			fprintf(output, "error\n");
		}
		else if(inital_link.mode == 'v')
		{
			fprintf(output, "( ");
			for(int i = 0; i < inital_link.size; i++)
			{
				fprintf(output, "%f ", inital_link.data[i]);
			}
			fprintf(output, ")");
			fprintf(output, " %c ", inital_link.op);
			fprintf(output, "( ");
			for(int i = 0; i < inital_link.size; i++)
			{
				fprintf(output, "%f ", inital_link.data[inital_link.size + i]);
			}
			fprintf(output, ") = ");
			fprintf(output, "( ");
			for(int i = 0; i < inital_link.size; i++)
			{
				fprintf(output, "%f ", deducting_link.data[i]);
			}
			fprintf(output, ")\n");
		}
		else if (inital_link.mode == 's')
		{
			if(inital_link.op == '!')
			{
				fprintf(output, "%f! = %f\n", inital_link.data[0], deducting_link.data[0]);
			}
			else
			{
				fprintf(output, "%f %c %f = %f\n", inital_link.data[0],inital_link.op, inital_link.data[1], deducting_link.data[0]);
			}
		}
	}

	//closing the file and clearing the memory
	fclose(output);
	free(inital_data);
	free(deducting_list);
	}
	while(rep == 'y');
	return 0;
}

