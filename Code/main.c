#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "matrix_circuit.h"

int main(int argc, char **argv) {

	Node* matrix = matrix_read(argc, argv);
	matrix_display_internal(matrix);
	int rows = rows_quantity(argv[1]);
    	int columns = columns_quantity(argv[1]);
	matrix_display_external(matrix, rows, columns);

	//matrix_devide(&matrix);
	//column_max(matrix);
	//printf("%d\n", column_penult_element(matrix));
	//column_penalt_element(matrix);
	Node* new_matr = matrix_devide(&matrix);
	matrix_display_internal(new_matr);
	return 0;
}	
