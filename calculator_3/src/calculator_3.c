/*
 ╔═════════════════════════[ХХХ]═════════════════════════════╗
 ║   Name        : calculator_3.c                            ║
 ║   Author      : Darya K  (https://github.com/Grief3749)   ║
 ║   Version     : 11.4                                       ║
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


typedef struct elem_data
{
	float data;
	struct elem_data *head, *previos;
}stack;

//checking for emptiness
int is_empty(stack **head_stack)
{
    stack *pointer = *head_stack;
	if(pointer->head == NULL)
	{
		return 1;
	}
		return 0;
}

//counter
int elemcount(stack **head_stack)
{
    stack *pointer = *head_stack;
	int count = 0;
	if(is_empty(&pointer) != 1)
	{
		count++;
		while(pointer->previos != NULL)
		{
			count++;
            pointer = pointer->previos;
		}
	}
	return count;
}

//new stack
stack* new_stack()
{
	stack* new_stack = malloc(sizeof(stack));
	new_stack->head = NULL;
	new_stack->previos = NULL;
	return new_stack;
}

//adding element to stack
void add(stack **head_stack, float data)
{
    stack *pointer = *head_stack;
	if(is_empty(&pointer) == 1)
	{
        pointer->data = data;
        pointer->head = pointer;
	}
	else
	{
		stack* new_elem = new_stack();
		new_elem->data = data;
		new_elem->previos = pointer;
		new_elem->head = new_elem;
        pointer->head = new_elem;
		while(pointer->previos != NULL)
		{
            pointer = pointer->previos;
            pointer->head = new_elem;
		}
        *head_stack = pointer->head;
	}
}

//take an element from the stack
float findstack(stack **head_stack)
{
    stack *pointer = *head_stack;
    float find_data = pointer->data;
    if(elemcount(&pointer) > 1)
    {
        pointer = pointer->previos;
        *head_stack = pointer;
        free(pointer->head);
        pointer->head = pointer;
        while (pointer->previos != NULL)
        {
            pointer->previos->head = pointer->head;
            pointer = pointer->previos;
        }
    }
    else
    {
        pointer->head = NULL;
    }
    return find_data;
}

//main function
int main(int argc, char* argv[])
{
	 setvbuf(stdout, NULL, _IONBF, 0);
	 setvbuf(stderr, NULL, _IONBF, 0);
	 char *path;
	 float data;
	 char op, extra;
	 float num1, num2;
	 int counter = 0;

	FILE *input, *output;
	path = calloc(100, sizeof(char));
	printf("enter the path to the file with input data:\n");
	scanf(" %100s", path);
	input = fopen(path, "r");
	free(path);
	//entering path to output file

	path = calloc(100, sizeof(char));
	printf("enter the path to the file where the output will be placed:\n");
	scanf(" %100s", path);
	output = fopen(path, "w");
	free(path);

	stack* data_store = new_stack();

	//main cycle
	while(feof(input) == 0)
	{
		//variables definition
		op = 0;
		data = 0;
		//reading numbers
		fscanf(input, "%f", &data);
		if(data == 0){
			fscanf(input, "%c", &extra);

		}
		//reading operations
		fscanf(input, " %c", &op);
		//calculations

		if(op == '+')//addition
		{
			counter++;
			num2 = findstack(&data_store);
			num1 = findstack(&data_store);
			add(&data_store, num1 + num2);
			fprintf(output, "%i. %f + %f = %f\n", counter, num1, num2, num1 + num2);
		}
		else if(op == '-')//subtraction
		{
			counter++;
			num2 = findstack(&data_store);
			num1 = findstack(&data_store);
			add(&data_store, num1 - num2);
			fprintf(output, "%i. %f - %f = %f\n", counter, num1, num2, num1 - num2);
		}
		else if(op == '*')//multiplication
		{
			counter++;
			num2 = findstack(&data_store);
			num1 = findstack(&data_store);
			add(&data_store, num1 * num2);
			fprintf(output, "%i. %f * %f = %f\n", counter, num1, num2, num1 * num2);
		}
		else if(op == '/')//division
		{
			counter++;
			num2 = findstack(&data_store);
			num1 = findstack(&data_store);
			add(&data_store, num1 / num2);
			fprintf(output, "%i. %f / %f = %f\n", counter, num1, num2, num1 / num2);
		}
		//adding to stack
		else{
			add(&data_store, data);
		}
		//reading a character
		while(op != ' ')
		{
			fscanf(input, "%c", &op);
		}
	}
	fclose(output);
	fclose(input);
	fprintf(output, "answer: %f", findstack(&data_store));
	return 0;
}
