#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "complex.h"
#include "matrix_circuit.h"

typedef enum {S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15} State;


void destroy(Node *matrix)
{
    if (matrix) {
        destroy(matrix->next);
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
	printf("Type: program -repinfo to gain more information about matrix representation\n");

}


Node* matrix_divide(Node *matrix, int column_id_devide, complex max)
{
	//int column_id_devide = column_penult_element(matrix);
	//complex max = element_max_find(matrix);

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
	printf("Two cells correspond to a nonzero element: the first\n");
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

	return(rows);
	fclose(file);
	
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
    double a, b;
    State s = S1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            do {
            c = fgetc(file);
            switch (s) {
                        case S1 :                       
                            if (c == '-') {
                                s = S2;
                            } else 
                            if (isdigit(c) && (c != '0')) {
                                a = translate_to_number(c);
                                s = S6;
                            } else
                            if (c == '0') {
                                element.a=0.0;
                                element.b=0.0;
                                break;
                            }  

                            break;
                        case S2:                                      
                            if (isdigit(c)) {
                                a = translate_to_number(c);
                            }
                            s = S3;
                            break;
                        case S3:                                     
                            if (c == '.') {
                                s = S4;
                            }
                            break;
                        case S4:
                            if (isdigit(c)) {
                                element.a = -(a + translate_to_number(c) / 10.0);
                            }
                            s = S5;
                            break;
                        case S5:
                            if (c == '-') {
                                s = S8;
                            } else 
                            if (c == '+') {
                                s = S13;
                            }
                            break;
                        case S6:  
                            if (c == '.') {
                                s = S7;
                            }
                            break;   
                        case S7:
                            if (isdigit(c)) {
                                element.a = a + translate_to_number(c) / 10.0;
                            }   
                            s = S5;
                            break;     
                        case S8 :
                            if (isdigit(c)) {
                                b = translate_to_number(c);
                            }
                            s = S9;
                            break;    
                        case S9: 
                            if (c == '.') {
                                s = S10;
                            }
                            break; 
                        case S10:   
                            if (isdigit(c)) {
                                element.b = -(b + translate_to_number(c) / 10.0);
                            }
                            s = S11;
                            break; 
                        case S11:
                            if (c == 'i') {
                                s = S12;
                            } 
                            break;
                        case S12:
                            if (isspace(c)){
                                s = S1;
                            }  
                            break;
                        case S13:
                            if (isdigit(c)) {
                                b = translate_to_number(c);
                            }          
                            s = S14;
                            break;
                        case S14: 
                            if (c == '.') {
                                s = S15;
                            }
                            break;     
                        case S15:
                            if (isdigit(c)) {
                               element.b = b + translate_to_number(c) / 10.0;
                            }
                            
                            s = S11;
                            break; 
                        }    
                } while (c != ' '); 
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


Node* matrix_read(char *filename) {

    FILE *in = fopen(filename, "r");
    int rows =rows_quantity(&filename[0]);
    int columns = columns_quantity(&filename[0]);
 	double a, b;
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
	                                s = S2;
	                            } else 
	                            if (isdigit(c) && (c != '0')) {
	                                a = translate_to_number(c);
	                                s = S6;
	                            } else
	                            if (c == '0') {
	                                element.a=0.0;
	                                element.b=0.0;
	                                break;
	                            }
	                            break;
	                        case S2:                                      ;
	                            if (isdigit(c)) {
	                                a = translate_to_number(c);
	                            }
	                            s = S3;
	                            break;
	                        case S3:                                     
	                            if (c == '.') {
	                                s = S4;
	                            }
	                            break;
	                        case S4:
	                            if (isdigit(c)) {
	                                element.a = -(a + translate_to_number(c) / 10.0);
	                            }
	                            s = S5;
	                            break;
	                        case S5:
	                            if (c == '-') {
	                                s = S8;
	                            } else 
	                            if (c == '+') {
	                                s = S13;
	                            }
	                            break;
	                        case S6:  
	                            if (c == '.') {
	                                s = S7;
	                            }
	                            break;   
	                        case S7:
	                            if (isdigit(c)) {
	                                element.a = a + translate_to_number(c) / 10.0;
	                            }   
	                            s = S5;
	                            break;     
	                        case S8 :
	                            if (isdigit(c)) {
	                                b = translate_to_number(c);
	                            }
	                            s = S9;
	                            break;    
	                        case S9: 
	                            if (c == '.') {
	                                s = S10;
	                            }
	                            break; 
	                        case S10:   
	                            if (isdigit(c)) {
	                                element.b = -(b + translate_to_number(c) / 10.0);
	                            }
	                            s = S11;
	                            break; 
	                        case S11:
	                            if (c == 'i') {
	                                s = S12;
	                            } 
	                            break;
	                        case S12:
	                            if (isspace(c)){
	                                s = S1;
	                            }  
	                            break;
	                        case S13:
	                            if (isdigit(c)) {
	                                b = translate_to_number(c);
	                            }          
	                            s = S14;
	                            break;
	                        case S14: 
	                            if (c == '.') {
	                                s = S15;
	                            }
	                            break;     
	                        case S15:
	                            if (isdigit(c)) {
	                               element.b = b + translate_to_number(c) / 10.0;
	                            }
	                            
	                            s = S11;
	                            break; 
	                        }    
	                } while (c != ' '); 
			
	      	
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


int main (void) {

	char filename[20];

	scanf("%s", &filename);
	int rows=rows_quantity(&filename[0]);
	int columns=columns_quantity(&filename[0]);

	Node* matrix=matrix_read(&filename);
	

	
 	//matrix_display_internal(matrix);
	//matrix_display_external(matrix, rows, columns);
	//Node* new_matr = matrix;
	//matrix_divide(new_matr);
	//matrix_display_internal(new_matr);
	//matrix_display_external(new_matr, rows, columns);
	complex max = element_max_find(matrix);
	int column_max_id= column_max(matrix, max);
	int penult = column_penult_element(matrix, column_max_id, max);
	

	free(matrix);
	//free(new_matr);
	return 0;
}	
