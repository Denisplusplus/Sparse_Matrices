#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "matrix_circuit.h"

int main(int argc, char **argv) {
	
	Node* matrix = matrix_read(argc, argv);
	matrix_inside_display(matrix);


	return 0;
}	
