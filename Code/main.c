#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "complex.h"
#include "matrix_circuit.h"

#include "functions.h"





int main (void) {

	char filename[20];
	printf("Input the name of matrix file\n");
	scanf("%s", &filename);

	int rows    = rows_quantity(&filename[0]);		// GENERAL ACTIONS
	int columns = columns_quantity(&filename[0]);

    Node* matrix = matrix_read(&filename, rows, columns); // INPUTTED MATRIX
 	
	
	complex max = element_max_find(matrix);
	int column_max_id= column_max(matrix, max); // PREPARATION TO LAUNCH THE TASK
	int penult = column_penult_element(matrix, column_max_id, max);

	Node* new_matrix = matrix;					// LAUNCHING THE TASK
	matrix_divide(new_matrix, penult, max);
	
	int action = 0;
    do {
	    printf("\nMenu:\n");
	    printf("1) Print internal representation of the matrix \n");
	    printf("2) Print external representation of the matrix \n");
	    printf("3) Perform the task and print internal matrix representation \n");
	    printf("4) Perform the task and print external matrix representation \n");
	    printf("5) Destroy matrix\n");
	    printf("6) Information about representation of the matrix\n");
	    printf("7) Information about the task\n");
	    printf("0) Exit\n");
	    printf("Input the action number: ");
        scanf("%d", &action);
        switch (action)
        {
                case 1:
 					matrix_display_internal(matrix);
                    break;  
                case 2:
                    matrix_display_external(matrix ,rows, columns);
                    break;
                case 3:
                    matrix_display_internal(new_matrix);
                    break;
                case 4:
                	matrix_display_external(new_matrix, rows, columns);
                	break;
                case 5:
                	matrix_destroy(matrix);	
                	break;
                case 6:
                    information_about_representation();
                    break;
                case 7:
                    information_about_task();
                    break;    
                case 0:
                	matrix_destroy(matrix);	
                default:
                	matrix_destroy(matrix);	
                    {printf("An error occurred. Try input 5 to find the solution\n");}
                    break;
        }
    } while (action != 0);
		
	return 0;
}	
