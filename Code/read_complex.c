void read(int argc, char **argv) {

    FILE *in = fopen(argv[1], "r");

    int rows = 2;
    int columns = 2;
    double a, b, a_t, b_t;
    char c;
    complex x;
    State s = S1;
     do {
        c = fgetc(in);
        switch (s) {
            case S1 :                       
                if (c == '-') {
                    s = S2;
                } else 
                if (isdigit(c)) {
                    a = (double)(c) -48.0;
                    s = S6;
                }
                break;
            case S2:                                      
                if (isdigit(c)) {
                    a = (double)(c) -48.0;
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
                    a_t = (double)(c) -48.0;
                    x.a = -(a + a_t / 10);
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
                    a_t = (double)(c) -48.0;
                    x.a = a + a_t / 10;
                }   
                s = S5;
                break;     
            case S8 :
                if (isdigit(c)) {
                    b = (double)(c) -48.0;
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
                    b_t = (double)(c) -48.0;
                    x.b = -(b + b_t / 10);
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
                    b = (double)(c) -48.0;
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
                    b_t = (double)(c) -48.0;
                    x.b = b + b_t / 10;
                }
                complex_print(x);
                s = S11;
                break; 
            }    
    } while (c != EOF); 

    fclose(in);
 
}

int main (int argc, char **argv) {


    read(argc, argv);



	return 0;
}	
