/*
 ╔═════════════════════════[ХХХ]═════════════════════════════╗
 ║   Name        : calculator_3.c                            ║
 ║   Author      : Darya K  (https://github.com/Grief3749)   ║
 ║   Version     : 9.1                                       ║
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

//definition of functions for working with queue

//definition new structure data
struct inital_data
{
    char op;
    char mode;
    int size;
    float *inital_data;
};


//definition of new type
typedef struct type_list
{
    struct inital_data inital_data;
    struct type_list *next;
}list;

//creating new list
list *newlist(struct inital_data inital_data){
    list *newlist = malloc(sizeof(list));
    newlist->inital_data = inital_data;
    newlist->next = NULL;
    return newlist;
}

//adding to beginning of list
void addfirst(list **headlist, struct inital_data inital_data){
    list *addfirst = newlist(inital_data);
    addfirst->next = *headlist;
    *headlist = addfirst;
}

//adding to end of list
void addlast(list **headlist, struct inital_data inital_data){
    list *addlast = newlist(inital_data);
    list *currentlist = *headlist;
    while(currentlist->next != NULL){
        currentlist = currentlist->next;
    }
    currentlist->next = addlast;
}

//adding after a definite element
void add(list **headlist, struct inital_data inital_data, int serialnum){
    list *addlist = newlist(inital_data);
    list *currentlist = *headlist;
    int current_serialnum = 0;
    while(currentlist->next != NULL){
        if(current_serialnum == serialnum){
            addlist->next = currentlist->next;
            currentlist->next = addlist;
        }
        current_serialnum++;
        currentlist = currentlist->next;
    }
}

//main function
int main(int argc, char *argv[]){
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    char repeat = 'n';
    int deg;
    int factorial;
    char *path;

    do{

		FILE *input, *output;
		path = calloc(100, sizeof(char));
		printf("enter the path to the file with input data:\n");
		scanf(" %100s", path);
		input = fopen(path, "r");
		free(path);
		struct inital_data elem;
		list *inital_data = newlist(elem);
		while(feof(input) == 0){
			fscanf(input, " %c", &elem.op);
			fscanf(input, " %c", &elem.mode);
			if (elem.mode == 'v'){
				fscanf(input, "%i", &elem.size);
				elem.inital_data = malloc(elem.size*sizeof(double));
				for(int i=0; i < elem.size*2; i++)
				{
					fscanf(input, "%f", &elem.inital_data[i]);
				}
				addlast(&inital_data, elem);
			} else if(elem.mode == 's') {
				if(elem.op == '!'){
					elem.inital_data = malloc(sizeof(double));
					fscanf(input, "%f", &elem.inital_data[0]);
				}
				else {
					elem.inital_data = malloc(2 * sizeof(double));
					fscanf(input, "%f", &elem.inital_data[0]);
					fscanf(input, "%f", &elem.inital_data[1]);
				}
				//adding new element to end of list
				addlast(&inital_data, elem);
			}
		}
		//closing file
		fclose(input);
		list *pointer = inital_data;
		struct inital_data deducting_elem;
		deducting_elem.inital_data = malloc(inital_data->inital_data.size*sizeof(double));
		list *deducting_list = newlist(deducting_elem);
		while(pointer->next != NULL) {
			pointer = pointer->next;
			deducting_elem.inital_data = malloc(inital_data->inital_data.size*sizeof(double));
			//working with vectors
			if(pointer->inital_data.mode == 'v')
			{
				switch (pointer->inital_data.op)
				{
					case '+':
						for(int i=0; i < pointer->inital_data.size; i++)
						{
							deducting_elem.inital_data[i] = pointer->inital_data.inital_data[i] + pointer->inital_data.inital_data[pointer->inital_data.size+i];
						}
						break;
					case '-':
						for(int i=0; i < pointer->inital_data.size; i++)
						{
							deducting_elem.inital_data[i] = pointer->inital_data.inital_data[i] - pointer->inital_data.inital_data[pointer->inital_data.size+i];
						}
						break;
					case '*':
						for(int i=0; i < pointer->inital_data.size; i++)
						{
							deducting_elem.inital_data[i] = pointer->inital_data.inital_data[i] * pointer->inital_data.inital_data[pointer->inital_data.size+i];
						}
						break;
					default:
						deducting_elem.op = 'e';
						break;
				}
			}
			//working with numbers
			else if(pointer->inital_data.mode == 's')
			{
				if (pointer->inital_data.op == '!' || pointer->inital_data.op == '^')
				{
					switch (pointer->inital_data.op)
					{
						case '!'://factorial
							factorial = 1;
							if(pointer->inital_data.inital_data[0] == 0)
							{
								deducting_elem.inital_data[0] = 1;
							}
							else
							{
								for(int i=1; i <= pointer->inital_data.inital_data[0]; i++)
								{
									factorial=factorial*i;
								}
								deducting_elem.inital_data[0] = factorial;
							}
							break;

						case '^'://exponentiation
							deg = 1;
							if(pointer->inital_data.inital_data[1] == 0)
							{
								deducting_elem.inital_data[0] = 1;
							}
							else if (pointer->inital_data.inital_data[1] < 0)
							{
								for(int i=1;i <= pointer->inital_data.inital_data[1];i++)
								{
									deg = deg / pointer->inital_data.inital_data[0];
								}
								deducting_elem.inital_data[0] = deg;
							}
							else
							{
								for(int i=1;i<=pointer->inital_data.inital_data[1];i++)
								{
									deg = deg * pointer->inital_data.inital_data[0];
								}
								deducting_elem.inital_data[0] = deg;
							}
							break;
						default:
							deducting_elem.op = 'e';
							break;
					}
				}
				else
				{
					switch (pointer->inital_data.op)
					{
					//addition
						case '+':
							deducting_elem.inital_data[0] = pointer->inital_data.inital_data[0]+pointer->inital_data.inital_data[1];
							break;
							//difference
						case '-':
							deducting_elem.inital_data[0] = pointer->inital_data.inital_data[0]-pointer->inital_data.inital_data[1];
							break;
						//multiplication
						case '*':
							deducting_elem.inital_data[0] = pointer->inital_data.inital_data[0]*pointer->inital_data.inital_data[1];
							break;
						//division
						case '/':
							deducting_elem.inital_data[0] = pointer->inital_data.inital_data[0]/pointer->inital_data.inital_data[1];
							break;
						default:
							deducting_elem.op = 'e';
							break;
					}
				}
			}
			else
			{
				deducting_elem.op = 'e';
			}
			//adding new element to end of list
			addlast(&deducting_list,deducting_elem);
		}
		path = calloc(100, sizeof(char));
		printf("enter the path to the file where the output will be placed:\n");
		scanf(" %100s", path);
		output = fopen(path, "w");
		free(path);
		pointer = inital_data;
		////output working with vectors
		while(pointer->next != NULL){
			pointer = pointer->next;
			deducting_list = deducting_list->next;
			if(deducting_list->inital_data.op == 'e'){
				fprintf(output, "error\n");
			}
			else if(pointer->inital_data.mode == 'v'){
				fprintf(output, "( ");
				for(int i = 0; i < pointer->inital_data.size; i++){
					fprintf(output, "%f ", pointer->inital_data.inital_data[i]);
				}
				fprintf(output, ")");
				fprintf(output, " %c ", pointer->inital_data.op);
				fprintf(output, "( ");
				for(int i = 0; i < pointer->inital_data.size; i++){
					fprintf(output, "%f ", pointer->inital_data.inital_data[pointer->inital_data.size + i]);
				}
				fprintf(output, ") = ");
				if(pointer->inital_data.op == '\''){
					fprintf(output,"%f\n", deducting_list->inital_data.inital_data[0]);
				} else {
					fprintf(output, "( ");
					for(int i = 0; i < pointer->inital_data.size; i++){
						fprintf(output, "%f ", deducting_list->inital_data.inital_data[i]);
					}
					fprintf(output, ")\n");
				}//output working with numbers
			} else if (pointer->inital_data.mode == 's'){
				if(pointer->inital_data.op == '!'){
					fprintf(output, "%f! = %f\n", pointer->inital_data.inital_data[0], deducting_list->inital_data.inital_data[0]);
				} else {
					fprintf(output, "%f %c %f = %f\n", pointer->inital_data.inital_data[0],pointer->inital_data.op, pointer->inital_data.inital_data[1], deducting_list->inital_data.inital_data[0]);
				}
			}
		}
        //closing file and clearing memory
		fclose(output);
		free(inital_data);
		free(pointer);
		free(deducting_list);
		//prompt to repeat the program and select new files
        printf("start over?\n'y' - yes\'n' - no\n");
		scanf(" %c", &repeat);
    }
    while(repeat == 'y');
    return 0;
}

