#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "matrix_circuit.h"


Node* matrix_read(int argc, char **argv);
void matrix_display_internal(Node* matrix);
void matrix_display_external(Node* matrix, int rows, int columns);
int element_find(Node* matrix, int i, int j);
void information_about_representation();
void add(Node **matrix, int data, int row);
int non_zero_str(int row, char* filename, int rows, int columns);
int columns_quantity(char* filename);
int rows_quantity(char* filename);

#endif
