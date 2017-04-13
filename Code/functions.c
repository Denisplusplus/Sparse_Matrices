#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "matrix_circuit.h"



void insert(Node *matrix, Node *new_node)
{
	if (matrix->_next == NULL) {
		matrix->_next = new_node;
		return;
	}	
	
	insert(matrix->_next, new_node);
}

void listprint(Node *matrix)
{
  Node *p;
  p = matrix;
  do {
    printf("%d ", p->_value); // вывод значения элемента p
    p = p->_next; // переход к следующему узлу
  } while (p != NULL);
}


Node* node_new(void) {

    Node* newNode=(Node *)malloc(sizeof(Node));
    newNode->_rows_id = 0;
    newNode->_value = 0;
    newNode->_next = NULL;

    return newNode;
}



void matrix_read(int argc, char **argv) {

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

    Node* matrix = node_new();
    for (int row = 0; row < rows; row++) {
    	for (int column = 0; column < columns; column++) {
    		fscanf(in, "%d", &element);
    		if (element != 0) { 
				Node* new_node = node_new(); 
				new_node->_value = element; 
				insert(matrix, new_node);
			
			} 
                        
    	}	
    }
  
    	
   listprint(matrix);
    
