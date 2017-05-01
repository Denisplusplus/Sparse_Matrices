#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "complex.h"





typedef enum {S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15} State;
double translate_to_number(char c)
{
	return((double)(c) -48.0);
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

void matrix_read(char *filename) {

    FILE *in = fopen(filename, "r");
    int rows =4;
    int columns = 4;

    for (int row = 0; row < rows; row++) {
    	for (int column = 0; column < columns; column++) {
	      	printf("%d\n", non_zero_str(row, &filename, rows, columns));

    	}
   
    }

    fclose(in);

   
 
}


int main (void) {

	char filename[20];

	scanf("%s", &filename);

	matrix_read(&filename);


/*for (int i=0; i<4; i++) {
		printf("%d\n", non_zero_str(i, &filename, 4, 4));
}
*/
	return 0;
}	
