
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "complex.h"
#include "matrix_circuit.h"

#include "functions.h"

typedef enum {S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15} State;


void matrix_destroy(Node *matrix)
{
    if (matrix) {
        matrix_destroy(matrix->next);
    }

    free(matrix);
}  


double translate_to_number(char c)
{
	return((double)(c) - 48.0);
}


void matrix_display_internal(Node* matrix)
{	
	printf("\nHere is internal representation of matrix \n");
	printf("Column/Row  Value \n");
	while (matrix) {
		printf("     %d      ", matrix->columns_id);
		complex_print(matrix->value);
		matrix=matrix->next;
	}


}


Node* matrix_divide(Node *matrix, int column_id_devide, complex max)
{
	while (matrix) {
		if ((matrix->columns_id) == column_id_devide) {
			matrix->value = complex_divide((matrix->value), max); 	
		}	
		matrix = matrix->next;
	}

	return(matrix);
}


int column_penult_element(Node* matrix, int column_max_id, complex element_max)
{
	int penult = 0;

	while (matrix) {
		if ((matrix->columns_id) && (equal(matrix->value,element_max)) && ((matrix->columns_id) < column_max_id)  && ((matrix->columns_id) >= penult)) {
			penult = matrix->columns_id;
		}

		matrix = matrix->next;
	}
	if (penult == 0) {
		return(column_max_id);
	}
	return (penult);
}


int column_max(Node* matrix, complex max)
{
	
	int column_max_number = 0;
	while (matrix) {
		if ((matrix->columns_id) && (equal(matrix->value, max)) && ((matrix->columns_id) > column_max_number)) {
			column_max_number = matrix->columns_id;
		}
		matrix = matrix->next;
	}
	return column_max_number;

}

complex element_max_find(Node *matrix)
{	
	complex max = element_zero();
	while(matrix) {
		if ((complex_abs(matrix->value) > complex_abs(max)) && (matrix->columns_id)) {
			max = matrix->value;
		}
		matrix = matrix->next;
	}		
	return(max);
}


complex element_find(Node* matrix, int i, int j)
{
	
	while(matrix){
		if ((matrix->columns_id == 0.0) && equal(matrix->value, complexing(i))) {
			matrix = matrix->next;
			while(matrix) {
				if (matrix->columns_id == 0.0) {
					return element_zero();
				}
				if (matrix->columns_id == j) {
					return(matrix->value);
				} else {
					matrix=matrix->next;
				}
			}	
		} else {
			matrix=matrix->next;
		}
	}
	return element_zero();
}


void matrix_display_external(Node* matrix, int rows, int columns)
{
	printf("\nHere is external representation of matrix \n");
	complex value;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			value = element_find(matrix, i+1, j+1);
			complex_print(value);
		}
		printf("\n");
	}
	printf("\n");
}

void information_about_representation()
{
	printf("\nTwo cells correspond to a nonzero element: the first\n");
	printf("contains the column number, the second contains the value\n"); 
	printf("of the element. A zero in the first cell indicates the end of the\n");
	printf("line, and the second cell in this case contains the number of the\n"); 
	printf("next stored line. Zeros in both cells are a sign of the end of the\n");
	printf("list of non-zero elements \n\n");
}


int rows_quantity(char* filename)
{	
	FILE *file = fopen(filename, "r");
	int rows = 1;
	char c;
  	while ((c = fgetc(file)) != EOF) {
        if (c=='\n') {
            rows++;
        }
    }
    fclose(file);
	return(rows);
	
	
}

int columns_quantity(char* filename)
{
	FILE *file = fopen(filename, "r");
	char c;
    int columns = 0; // because the number of columns bigger than amount of spaces in 1;

    while ((c = fgetc(file)) !='\n') {
        if (isspace(c)) {
            columns++;
        }
    }
	
	fclose(file);
	return(columns);
}

int non_zero_str(int row, char* filename, int rows, int columns)
{
    FILE *file = fopen(filename, "r");
    int q = 0; //quantity of zero elements
    int c;
    complex element; 
    double re, im;
    State s = S1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            do {
                c = fgetc(file);
                switch (s) {
                            case S1 :      
                                if (c == '-') {
                                    s = S10;
                                    break;
                                } 
                                if (isdigit(c)) {
                                    re = translate_to_number(c);
                                }  
                                if (isspace(c)) {
                                    s = S1;
                                    break;
                                }
                                s = S2;
                                break;
                            case S2:                                      
                                if (c == '.') {
                                    s = S3;
                                }
                                break;
                            case S3:                                     
                                 if (isdigit(c)) {
                                    element.re = re + translate_to_number(c) / 10.0;
                                    element.im = 0.0;
                                }
                                s = S4;
                                break;
                            case S4:
                                if (c == '+') {
                                    s = S5;
                                } 
                                if (c == '-') {
                                    s = S13;
                                }
                                if (isspace(c)) {
                                    s= S1;
                                }

                                break;
                            case S5:
                                if (isdigit(c)) {
                                    im = translate_to_number(c);
                                }
                                s= S6;
                                break;
                            case S6:  
                                if (c == '.') {
                                    s = S7;
                                }
                                break;   
                            case S7:
                                if (isdigit(c)) {
                                    element.im = im + translate_to_number(c) / 10.0;
                                }   
                                s = S8;
                                break;     
                            case S8 :
                                if (c == 'i') {
                                    s = S9;
                                }
                                break;    
                            case S9: 
                               if (isspace(c)){
                                    s = S1;
                                }  
                                break;
                            case S10:
                                if (isdigit(c)) {
                                    re = translate_to_number(c);
                                }
                                s = S11;
                                break;
                            case S11:
                                if (c == '.') {
                                    s = S12;
                                }   
                                break;
                            case S12:
                                if (isdigit(c)) {
                                    element.re = -(re + translate_to_number(c) / 10.0);
                                    element.im = 0.0;
                                }   
                                s = S4;
                                break;   
                            case S13:
                                if (isdigit(c)) {
                                    im = translate_to_number(c);
                                    s = S14;
                                }   
                                break;
                            case S14:
                                if (c == '.') {
                                    s = S15;
                                }   
                                break;        
                            case S15:
                                if (isdigit(c)) {
                                    element.im = -(im + translate_to_number(c) / 10.0);
                                    s = S8;
                                }   
                                break;

                            } 
                }  while (c != ' '); 
                    
                if ((i == row ) && (!element_not_zero(element))) {
                	q++;
           		}
        }
    }
     fclose(file);
    if (q == columns) {
        return 0;
    } 
    return 1;
            
}


void add(Node **matrix, int column, complex data)
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


Node* matrix_read(char *filename, int rows, int columns) {

    FILE *in = fopen(filename, "r");
  
 	double re, im;
    int c;
    complex element;
	State s = S1;
	Node *matrix;
    matrix = NULL;
    for (int row = 0; row < rows; row++) {
    	for (int column = 0; column < columns; column++) {
	    	    do {
                c = fgetc(in);
                switch (s) {
                            case S1 :      
                                if (c == '-') {
                                    s = S10;
                                    break;
                                } 
                                if (isdigit(c)) {
                                    re = translate_to_number(c);
                                }  
                                if (isspace(c)) {
                                    s = S1;
                                    break;
                                }
                                s = S2;
                                break;
                            case S2:                                      
                                if (c == '.') {
                                    s = S3;
                                }
                                break;
                            case S3:                                     
                                 if (isdigit(c)) {
                                    element.re = re + translate_to_number(c) / 10.0;
                                    element.im = 0.0;
                                }
                                s = S4;
                                break;
                            case S4:
                                if (c == '+') {
                                    s = S5;
                                } 
                                if (c == '-') {
                                    s = S13;
                                }
                                if (isspace(c)) {
                                    s= S1;
                                }

                                break;
                            case S5:
                                if (isdigit(c)) {
                                    im = translate_to_number(c);
                                }
                                s= S6;
                                break;
                            case S6:  
                                if (c == '.') {
                                    s = S7;
                                }
                                break;   
                            case S7:
                                if (isdigit(c)) {
                                    element.im = im + translate_to_number(c) / 10.0;
                                }   
                                s = S8;
                                break;     
                            case S8 :
                                if (c == 'i') {
                                    s = S9;
                                }
                                break;    
                            case S9: 
                               if (isspace(c)){
                                    s = S1;
                                }  
                                break;
                            case S10:
                                if (isdigit(c)) {
                                    re = translate_to_number(c);
                                }
                                s = S11;
                                break;
                            case S11:
                                if (c == '.') {
                                    s = S12;
                                }   
                                break;
                            case S12:
                                if (isdigit(c)) {
                                    element.re = -(re + translate_to_number(c) / 10.0);
                                    element.im = 0.0;
                                }   
                                s = S4;
                                break;   
                            case S13:
                                if (isdigit(c)) {
                                    im = translate_to_number(c);
                                    s = S14;
                                }   
                                break;
                            case S14:
                                if (c == '.') {
                                    s = S15;
                                }   
                                break;        
                            case S15:
                                if (isdigit(c)) {
                                    element.im = -(im + translate_to_number(c) / 10.0);
                                    s = S8;
                                }   
                                break;

                            } 
                }  while (c != ' '); 
			
	      	
			if ((column == 0) && non_zero_str(row, &filename[0], rows, columns)) {
    			add(&matrix, 0, complexing(row + 1));
    			
    		} 
    		if (element_not_zero(element)) { 
    		    add(&matrix, (column+1), element);
			} 
			if ((row == rows - 1) && (column == columns - 1)) {
				add(&matrix, 0, element_zero());
			}

    	}
    	
    }

    fclose(in);
   return(matrix);
}

void information_about_task() 
{

	printf("\nDetermine the maximum modulo element of the matrix\n");
	printf("and perform the dividing all elements of the column\n");
	printf("in which it is on this element, if quantity of such\n");
	printf("elements is more than one, then make the dividing with\n");
	printf("next-to-last column containing such an element\n\n");

}
