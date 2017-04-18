#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "matrix_circuit.h"


int main(int argc, char **argv) {

    Node* matrix = matrix_read(argc, argv);
    int rows = rows_quantity(argv[1]);
    int columns = columns_quantity(argv[1]);
    Node* new_matr = matrix;

	

    int action = 0;
    do {
	    printf("\nMenu:\n");
	    printf("1) Print internal representation of the matrix \n");
	    printf("2) Print external representation of the matrix \n");
	    printf("3) Perform the task and print internal matrix representation \n");
	    printf("4) Perform the task and print external matrix representation \n");
	    printf("5) Help\n");
	    printf("6) Information about representation of the matrix\n");
	    printf("0) Exit\n");
	    printf("Input the action number: ");
        scanf("%d", &action);
        switch (action)
        {
                case 1:
                    matrix_display_internal(matrix);
                    break;
                case 2:
                    matrix_display_external(matrix, rows, columns);
                    break;  
                case 3:
                    matrix_display_internal(new_matr);
                    break;
                case 4:
                    matrix_display_external(new_matr, rows, columns);
                    break;
                case 5:
                    help();
                    break;
                case 6:
                    information_about_representation();
                    break;
                case 0:
                    break;
                default:
                    {printf("An error occurred. Try input 5 to find the solution\n");}
                    break;
        }
    } while (action != 0);
	
	return 0;
}	
