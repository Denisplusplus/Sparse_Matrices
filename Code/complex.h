#ifndef __COMPLEX_H__
#define __COMPLEX_H__


typedef struct {
     double a,b;
 } complex;

complex complex_divide(complex x, complex y);
double complex_absolute(complex x);
void complex_print(complex x);
#endif
