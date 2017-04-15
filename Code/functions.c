#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "matrix_circuit.h"


void matrix_inside_display(Node* matrix)
{
	while (matrix) {
		printf("%d ", matrix->rows_id);
		printf("%d ", matrix->value);
		
		printf("\n");
		matrix=matrix->next;
	}
}


void add(Node **matrix, int data, int column)
{
    Node *temp = NULL; 
    if(!(*matrix))
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->next = NULL;
        temp->value = data;
        temp->rows_id = column;
        *matrix = temp;
        return;
    }
    add(&(*matrix)->next, data, column);
    free(temp);
} 

Node* matrix_read(int argc, char **argv) {

	FILE *in = fopen(argv[1], "r");

	if (argc != 2) {
        printf("Something went wrong. Use key -help to find the solution\n");
        exit(1);
    } 
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(2);
    }
    // count the rows
    int rows = 0;
    while (! feof(in)) {
        fscanf(in, "%*[^\n]%*c");
        rows++;
    }

    rewind(in);
    
    char c;
    int columns = 1; // because the number of columns bigger than amount of spaces in 1;

    while ((c = fgetc(in)) !='\n') {
        if (isspace(c)) {
            columns++;
       }
    }
    
    rewind(in);
    
    // read matrix from file
    int element = 0;
    Node *matrix;
    matrix = NULL;
    for (int row = 0; row < rows; row++) {
    	for (int column = 0; column <columns; column++) {
    		fscanf(in, "%d", &element);
    		if (column == 0) {
    			add(&matrix, (row + 1), 0);
    		
    		}
    		if (element != 0) { 
    		    add(&matrix, element, (column+1));
			}	
                        
    	}	
    }
 	return(matrix);
    
  
    fclose(in);
    
}

