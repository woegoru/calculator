/*
 ╔═════════════════════════[ХХХ]═════════════════════════════╗
 ║   Name        : calculator_3.c                            ║
 ║   Author      : Darya K  (https://github.com/Grief3749)   ║
 ║   Version     : 5.6                                       ║
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

//adding lists from a prepared file

//basic data structure
struct inital_data{
	char op, mode;
	int size;
	float *data;
};

//creating a new type
typedef struct main_list{
	struct inital_data data;
	struct main_list *next, *previous, *head, *tail;
}list;

//creating new list
list* new_list(struct inital_data inital_data){
	list* new_list = malloc(sizeof(list));
	new_list->data = inital_data;
	new_list->next = NULL;
	return new_list;
}

//void check
int is_empty(list **headcontainer){
	list* extcontainer = *headcontainer;
	if(extcontainer->head == NULL){
		return 0;
	}
	else return 1;
}

//counter
int elementcounter(list **headcontainer){
	list* extcontainer = *headcontainer;
	int counter = 0;
	if(is_empty(&extcontainer) == 0){
		return counter;
	}
	else{
		while(extcontainer != NULL){
			counter++;
			extcontainer = extcontainer->next;
		}
		return counter;
	}
}

//adding an element to the beginning
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

//adding an element to the end
void addlast(list **headlist, struct inital_data inital_data){
	list* extlist = *headlist;
	list* newelement = new_list(inital_data);
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

//adding an element
void addtolist(list **headlist, struct inital_data inital_data, int number){
	list* extlist = *headlist;
	list* newelement = new_list(inital_data);
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
	list *inital_data = new_list(elem);

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
			addlast(&inital_data, elem);
		}
		else if(elem.mode == 'v')
		{
			fscanf(input, "%i", &elem.size);
			elem.data = malloc(elem.size*sizeof(double));
			for(int i=0; i < elem.size*2; i++)
			{
				fscanf(input, "%f", &elem.data[i]);
			}
			addlast(&inital_data, elem);
		}
	}

	//closing a file
	fclose(input);

	list* link = inital_data;
	struct inital_data deducing_elem;

	deducing_elem.data = malloc(inital_data->data.size*sizeof(double));
	list* output_list = new_list(deducing_elem);
	while(link->next != NULL)
	{
		link = link->next;
		deducing_elem.data = malloc(inital_data->data.size*sizeof(double));
		if(link->data.mode == 'v') //working with vectors
		{
			switch(link->data.op)
		{
				case '+':
					for(int i=0; i < link->data.size; i++) //addition
					{
						deducing_elem.data[i] = link->data.data[i] + link->data.data[link->data.size+i];
					}
					break;
				case '-':
					for(int i=0; i < link->data.size; i++) //subtraction
					{
						deducing_elem.data[i] = link->data.data[i] - link->data.data[link->data.size+i];
					}
					break;
				case '*':
					for(int i=0; i < link->data.size; i++) //multiplication
					{
						deducing_elem.data[i] = link->data.data[i] * link->data.data[link->data.size+i];
					}
					break;
				case '/':
					for(int i=0; i < link->data.size; i++) //division
					{
						deducing_elem.data[i] = link->data.data[i] / link->data.data[link->data.size+i];
					}
					break;
				default:
					deducing_elem.op = 'E';
					break;
		}
		}
		else if(link->data.mode == 's') //working with numbers
		{
			if(link->data.op == '!' || link->data.op == '^')
			{
				switch(link->data.op)
				{
				case '!': //finding the factorial
					fac = 1;
					if(link->data.data[0] == 0)
					{
						deducing_elem.data[0] = 1;
					}
					if(link->data.data[0] > 0)
					{
						for(int i=1; i <= link->data.data[0]; i++)
						{
							fac = i * fac;
						}
						deducing_elem.data[0] = fac;
					}
					else
					{
						deducing_elem.op = 'E';
					}
					break;
				case '^': //exponentiation
					deg = 1;
					if(link->data.data[0] == 0)
					{
						deducing_elem.data[0] = 1;
					}
					if(link->data.data[1] > 0)
					{
						for(int i=1; i <= link->data.data[1]; i++)
						{
							deg = deg * link->data.data[0];
						}
						deducing_elem.data[0] = deg;
					}
					if(link->data.data[1] < 0)
					{
						for(int i=1; i <= link->data.data[1]; i++)
						{
							deg = deg / link->data.data[0];
						}
						deducing_elem.data[0] = deg;
					}
					break;
				default:
					deducing_elem.op = 'E';
					break;
				}
			}
			else
			{
				switch(link->data.op)
				{
				case '+': //addition
					deducing_elem.data[0] = link->data.data[0] + link->data.data[1];
					break;
				case '-': //subtraction
					deducing_elem.data[0] = link->data.data[0] - link->data.data[1];
					break;
				case '*': //multiplication
					deducing_elem.data[0] = link->data.data[0] * link->data.data[1];
					break;
				case '/': //division
					deducing_elem.data[0] = link->data.data[0] / link->data.data[1];
					break;
				default:
					deducing_elem.op = 'E';
					break;

				}
			}
		}
		else
		{
			deducing_elem.op = 'E';
		}
		addlast(&output_list,deducing_elem);
	}
	output = fopen("output.txt", "w");
	link = inital_data;

	//working with output
	while(link->next != NULL)
	{
		link = link->next;
		output_list = output_list->next;
		if(output_list->data.op == 'E')
		{
			fprintf(output, "error\n");
		}
		else if(link->data.mode == 'v')
		{
			fprintf(output, "( ");
			for(int i = 0; i < link->data.size; i++)
			{
				fprintf(output, "%f ", link->data.data[i]);
			}
			fprintf(output, ")");

			fprintf(output, " %c ", link->data.op);
			fprintf(output, "( ");
			for(int i = 0; i < link->data.size; i++)
			{
				fprintf(output, "%f ", link->data.data[link->data.size + i]);
			}

			fprintf(output, ") = ");
			fprintf(output, "( ");
			for(int i = 0; i < link->data.size; i++)
			{
				fprintf(output, "%f ", output_list->data.data[i]);
			}
			fprintf(output, ")\n");

		}
		else if (link->data.mode == 's')
		{
			if(link->data.op == '!')
			{
				fprintf(output, "%f! = %f\n", link->data.data[0], output_list->data.data[0]);
			}
			else
			{
				fprintf(output, "%f %c %f = %f\n", link->data.data[0],link->data.op, link->data.data[1], output_list->data.data[0]);
			}
		}
	}

	//closing the file and clearing the memory
	fclose(output);
	free(inital_data);
	free(link);
	free(output_list);
	}
	while(rep == 'y');
	return 0;
}

