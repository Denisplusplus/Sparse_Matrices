#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "matrix_circuit.h"

int main(int argc, char **argv) {

	Node* matrix = matrix_read(argc, argv);
	//matrix_display_internal(matrix);
	int rows = rows_quantity(argv[1]);
    	int columns = columns_quantity(argv[1]);
	//matrix_display_external(matrix, rows, columns);

	return 0;
}	
