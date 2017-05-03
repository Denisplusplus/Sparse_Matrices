#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "complex.h"

void matrix_destroy(Node *matrix);
double translate_to_number(char c);
void matrix_display_internal(Node* matrix);
Node* matrix_divide(Node *matrix, int column_id_devide, complex max);
int column_penult_element(Node* matrix, int column_max_id, complex element_max);
int column_max(Node* matrix, complex max);
complex element_max_find(Node *matrix);
complex element_find(Node* matrix, int i, int j);
void matrix_display_external(Node* matrix, int rows, int columns);
void information_about_representation();
int rows_quantity(char* filename);
int columns_quantity(char* filename);
int non_zero_str(int row, char* filename, int rows, int columns);
Node* matrix_read(char *filename, int rows, int columns);


#endif
