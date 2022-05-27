/*
 ╔═════════════════════════[ХХХ]═════════════════════════════╗
 ║   Name        : calculator_3.c                            ║
 ║   Author      : Darya K  (https://github.com/Grief3749)   ║
 ║   Version     : 8.1                                       ║
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
struct inital_data{
    char op;
    char mode;
    int size;
    float *inital_data;
};


typedef struct elem{
    struct inital_data inital_data;
    struct elem *next, *previous, *head, *tail;
}qeue;


qeue *newqeue(){
	qeue *newqeue = malloc(sizeof(qeue));
    newqeue->next = NULL;
    newqeue->head = NULL;
    newqeue->tail = NULL;
    newqeue->previous = NULL;
    return newqeue;
}


int is_empty(qeue **headqeue){
	qeue *extelem = *headqeue;
    if(extelem->head == NULL){
        return 0;
    }
    else{
        return 1;
    }
}


int elemcounter(qeue **headqeue){
	qeue *extelem = newqeue();
    extelem = *headqeue;
    int counter = 0;
    if(is_empty(&extelem) == 0){
        return 0;
    }
    else{
        while (extelem != NULL){
            counter++;
            extelem = extelem->next;
        }
        return counter;
    }
}


void addtoqueue(qeue **headqueue, struct inital_data inital_data){
	qeue *extelem = newqeue();
	qeue *addelem = newqeue();
    extelem = *headqueue;
    if(elemcounter(&extelem) == 0){
        addelem->inital_data = inital_data;
        addelem->head = addelem;
        addelem->tail = addelem;
        extelem = addelem;
    }
    else{
        addelem->inital_data = inital_data;
        addelem->head = addelem;
        addelem->next = extelem;
        addelem->tail = extelem->tail;
        extelem->previous = addelem;
        while (extelem != NULL){
            extelem->head = addelem;
            extelem = extelem->next;
        }
        extelem = addelem;
    }
    *headqueue = extelem;
}


struct inital_data find(qeue **headqueue){
	qeue *extqueue = *headqueue;
    struct inital_data finddata;
    if (elemcounter(&extqueue) == 1){
        finddata = extqueue->inital_data;
        extqueue->next = NULL;
        extqueue->head = NULL;
        extqueue->tail = NULL;
        extqueue->previous = NULL;
    } else if (elemcounter(&extqueue) > 1){
        finddata = extqueue->tail->inital_data;
        extqueue = extqueue->tail->previous;
        extqueue->tail = extqueue;
        extqueue->next = NULL;
        while (extqueue->previous != NULL){
            extqueue = extqueue->previous;
            extqueue->tail = extqueue->next->tail;
        }
        extqueue = extqueue->head;
        *headqueue = extqueue;
    }
    return finddata;
}



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

        qeue *inital_data = newqeue();

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
            }
            //adding new element to end of queue
            addtoqueue(&inital_data, elem);
        }
        //closing file
        fclose(input);
        struct inital_data input_link, deducting_link;
        struct inital_data deducting_elem;
        input_link.inital_data = malloc(inital_data->inital_data.size*sizeof(double));
        deducting_link.inital_data = malloc(inital_data->inital_data.size*sizeof(double));
        deducting_elem.inital_data = malloc(inital_data->inital_data.size*sizeof(double));
        qeue *deducting_list = newqeue();
        qeue *deducting_queue_op = newqeue();
        while(is_empty(&inital_data) != 0) {
        	//getting an element from the queue
            input_link = find(&inital_data);
            //adding new element to end of queue
            addtoqueue(&deducting_queue_op,input_link);
            //allocation memory
            deducting_elem.inital_data = malloc(inital_data->inital_data.size*sizeof(double));
            //working with vectors
            if(input_link.mode == 'v')
            {
                switch (input_link.op)
                {

                    case '+': //addition
                        for(int i=0; i < input_link.size; i++)
                        {
                        	deducting_elem.inital_data[i] = input_link.inital_data[i] + input_link.inital_data[input_link.size+i];
                        }
                        break;

                    case '-'://difference
                        for(int i=0; i < input_link.size; i++)
                        {
                        	deducting_elem.inital_data[i] = input_link.inital_data[i] - input_link.inital_data[input_link.size+i];
                        }
                        break;

                    case '*'://multiplication
                        for(int i=0; i < input_link.size; i++)
                        {
                        	deducting_elem.inital_data[i] = input_link.inital_data[i] * input_link.inital_data[input_link.size+i];
                        }
                        break;
                    default:
                    	deducting_elem.op = 'e';
                        break;
                }
            }
            //working with numbers
            else if(input_link.mode == 's')
            {
                if (input_link.op == '!' || input_link.op == '^')
                {
                    switch (input_link.op)
                    {

                        case '!': //factorial
                            factorial = 1;
                            if(input_link.inital_data[0] == 0)
                            {
                            	deducting_elem.inital_data[0] = 1;
                            }
                            else
                            {
                                for(int i=1; i <= input_link.inital_data[0]; i++)
                                {
                                    factorial=factorial*i;
                                }
                                //output
                                deducting_elem.inital_data[0] = factorial;
                            }
                            break;
                        case '^': //exponentiation
                            deg = 1;
                            if(input_link.inital_data[1] == 0)
                            {
                            	deducting_elem.inital_data[0] = 1;
                            }
                            else if (input_link.inital_data[1] < 0)
                            {
                                for(int i=1;i <= input_link.inital_data[1];i++)
                                {
                                    deg = deg / input_link.inital_data[0];
                                }
                                deducting_elem.inital_data[0] = deg;
                            }
                            else
                            {
                                for(int i=1;i<=input_link.inital_data[1];i++)
                                {
                                    deg = deg * input_link.inital_data[0];
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
                    switch (input_link.op)
                    {
                        //addition
                        case '+':
                            deducting_elem.inital_data[0] = input_link.inital_data[0]+input_link.inital_data[1];
                            break;
                            //difference
                        case '-':
                        	deducting_elem.inital_data[0] = input_link.inital_data[0]-input_link.inital_data[1];
                            break;
                            //multiplication
                        case '*':
                        	deducting_elem.inital_data[0] = input_link.inital_data[0]*input_link.inital_data[1];
                            break;
                            //division
                        case '/':
                        	deducting_elem.inital_data[0] = input_link.inital_data[0]/input_link.inital_data[1];
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
            //adding new element to end of queue
            addtoqueue(&deducting_list,deducting_elem);
        }
        path = calloc(100, sizeof(char));
        printf("enter the path to the file where the output will be placed:\n");
        scanf(" %100s", path);
        output = fopen(path, "w");
        free(path);
        while(is_empty(&deducting_list) != 0){
        	//getting an element from the queue
            input_link = find(&deducting_queue_op);
            deducting_link = find(&deducting_list);
            if(deducting_link.op == 'e'){
                fprintf(output, "error\n");
            }
            //output working with vectors
            else if(input_link.mode == 'v'){
                fprintf(output, "( ");
                for(int i = 0; i < input_link.size; i++){
                    fprintf(output, "%f ", input_link.inital_data[i]);
                }
                fprintf(output, ")");
                fprintf(output, " %c ", input_link.op);
                fprintf(output, "( ");
                for(int i = 0; i < input_link.size; i++){
                    fprintf(output, "%f ", input_link.inital_data[input_link.size + i]);
                }
                fprintf(output, ") = ");
                if(input_link.op == '\''){
                    fprintf(output,"%f\n", deducting_link.inital_data[0]);
                } else {
                    fprintf(output, "( ");
                    for(int i = 0; i < input_link.size; i++){
                        fprintf(output, "%f ", deducting_link.inital_data[i]);
                    }
                    fprintf(output, ")\n");
                }
            //output working with numbers
            } else if (input_link.mode == 's'){
                if(input_link.op == '!'){
                    fprintf(output, "%f! = %f\n", input_link.inital_data[0], deducting_link.inital_data[0]);
                } else {
                    fprintf(output, "%f %c %f = %f\n", input_link.inital_data[0],input_link.op, input_link.inital_data[1], deducting_link.inital_data[0]);
                }
            }
        }
        //closing file and clearing memory
        fclose(output);
        free(inital_data);
        free(deducting_list);
        //repeat the program
        printf("start over?\n'y' - yes\'n' - no\n");
        scanf(" %c", &repeat);
    }
    while(repeat == 'y');
    return 0;
}

