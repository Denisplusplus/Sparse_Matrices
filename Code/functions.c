#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "matrix_circuit.h"


void help()
{
	printf("This program is required to work with inputed in file matrix.\n");
	printf("To start the progtam type in console ./program MATRIX_FILE \n\n");
}

Node* matrix_devide(Node *matrix)
{
	int column_id_devide = column_penult_element(matrix);
	int max = element_max_find(matrix);

	while (matrix) {
		if ((matrix->columns_id) == column_id_devide) {
			matrix->value = (matrix->value) / max; 	
		}	
		matrix = matrix->next;
	}

	return(matrix);
}

int column_penult_element(Node* matrix)
{
	int penult = 0;
	int column_max_id = column_max(matrix);
	int element_max = element_max_find(matrix);
	while (matrix) {
		if ((matrix->columns_id) && (matrix->value == element_max) && ((matrix->columns_id) < column_max_id)  && ((matrix->columns_id) >= penult)) {
			penult = matrix->columns_id;
		}

		matrix = matrix->next;
	}
	if (penult == 0) {
		return(column_max_id);
	}
	return (penult);
}
int column_max(Node* matrix)
{
	int max = element_max_find(matrix);
	int column_max_number = 0;
	while (matrix) {
		if ((matrix->columns_id) && (matrix->value == max) && ((matrix->columns_id) > column_max_number)) {
			column_max_number = matrix->columns_id;
		}

		matrix = matrix->next;
	}
	return(column_max_number);

}

int element_max_find(Node *matrix)
{	
	int max = 0;
	while(matrix) {
		if ((abs(matrix->value) > abs(max)) && (matrix->columns_id)) {
			max = matrix->value;
		}
		matrix = matrix->next;
	}		
	return(max);
}
int non_zero_str(int row, char* filename, int rows, int columns)
{
	FILE *file = fopen(filename, "r");
	int element = 0;
	int q = 0; //quantity of zero elements
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			fscanf(file, "%d", &element);
			if ((i == row ) && (element == 0)) {
				q++;
			}
		}
	}
	return !(q == columns);
	fclose(file);
}



int columns_quantity(char* filename)
{
	FILE *file = fopen(filename, "r");
	char c;
    int columns = 1; // because the number of columns bigger than amount of spaces in 1;

    while ((c = fgetc(file)) !='\n') {
        if (isspace(c)) {
            columns++;
        }
    }
	return(columns);
	fclose(file);
}


int rows_quantity(char* filename)
{	
	FILE *file = fopen(filename, "r");
	int rows = 0;
    while (! feof(file)) {
        fscanf(file, "%*[^\n]%*c");
        rows++;
    }

	return(rows);
	fclose(file);
}


void information_about_representation()
{
	printf("Two cells correspond to a nonzero element: the first\n");
	printf("contains the column number, the second contains the value\n"); 
	printf("of the element. A zero in the first cell indicates the end of the\n");
	printf("line, and the second cell in this case contains the number of the\n"); 
	printf("next stored line. Zeros in both cells are a sign of the end of the\n");
	printf("list of non-zero elements \n\n");
}


void matrix_display_internal(Node* matrix)
{	
	printf("\nHere is internal representation of matrix \n");
	printf("Column/Row  Value \n");
	while (matrix) {
		printf("     %d ", matrix->columns_id);
		printf("       %d\n", matrix->value);
		matrix=matrix->next;
	}
	printf("Type: program -repinfo to gain more information about matrix representation\n");

}

int element_find(Node* matrix, int i, int j)
{
	
	while(matrix){
		if ((matrix->columns_id == 0) && (matrix->value == i) ){
			matrix = matrix->next;
			while(matrix) {
				if (matrix->columns_id == 0) {
					return 0;
				}
				if ((matrix->columns_id == j)){
					return(matrix->value);
				} else {
					matrix=matrix->next;
				}
			}	
		} else {
			matrix=matrix->next;
		}
	}
	return 0;

}
void matrix_display_external(Node* matrix, int rows, int columns)
{
	printf("\nHere is external representation of matrix \n");
	int value = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			value = element_find(matrix, i+1, j+1);
			printf("%d ", value);
		}
		printf("\n");
	}
	printf("\n");
}


void add(Node **matrix, int column, int data)
{
    Node *temp = NULL; 
    if(!(*matrix))
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->next = NULL;
        temp->value = data;
        temp->columns_id = column;
        *matrix = temp;
        return;
    }
    add(&(*matrix)->next, column, data);
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
    
    int rows = rows_quantity(argv[1]);
    int columns = columns_quantity(argv[1]);
    // read matrix from file
    int element = 0;
    Node *matrix;
    matrix = NULL;
    for (int row = 0; row < rows; row++) {
    	for (int column = 0; column <columns; column++) {
    		fscanf(in, "%d", &element);
    		if (column == 0 && non_zero_str(row, argv[1], rows, columns)) {
    			add(&matrix, 0, (row + 1));
    		}
    		if (element != 0) { 
    		    add(&matrix, (column+1), element);
			}
			if ((row == rows - 1) && (column == columns - 1)) {
				add(&matrix, 0, 0);
			}	
                        
    	}	
    }
 	return(matrix);
    fclose(in);
}

