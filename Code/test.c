#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "complex.h"
#include "matrix_circuit.h"

double translate_to_number(char c)
{
	return((double)(c) -48.0);
}

typedef enum {S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15} State;
/*
int rows_quantity(char* filename)
{	
	FILE *file = fopen(filename, "r");
	int rows = 0;
    while (! feof(file)) {
        fscanf(file, "%*[^\n]%*c");
        rows++;
    }

	return(rows);
	fclose(file);
	
}*/



void read(int argc, char **argv) {

    FILE *in = fopen(argv[1], "r");

    int rows = 2;
    int columns = 3;
    double a, b;
    char c;
    complex x;
	State s = S1;
    for (int row = 0; row < rows; row++) {
    	for (int column = 0; column < columns; column++) {
    		printf("%d %d\n", row, column);
    	 do {
        	c = fgetc(in);
        	switch (s) {
           	 			case S1 :                       
			                if (c == '-') {
			                    s = S2;
			                } else 
			                if (isdigit(c)) {
			                    a = translate_to_number(c);
			                    s = S6;
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
			                    x.a = -(a + translate_to_number(c) / 10.0);
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
			                    x.a = a + translate_to_number(c) / 10.0;
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
			                    x.b = -(b + translate_to_number(c) / 10.0);
			                }
			                complex_print(x);
			                s = S11;
			                break; 
			            case S11:
			                if (c == 'i') {
			                    s = S12;
			                } 
			                break;
			            case S12:
			                if (isspace(c)){
			                    s=S1;
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
			                    x.b = b + translate_to_number(c) / 10.0;
			                }
			                complex_print(x);
			                s = S11;
			                break; 
			            }    
			    } while (c != ' '); 
    	}
    }




    fclose(in);
 
}



int main (int argc, char **argv) {


    read(argc, argv);



	return 0;
}	
