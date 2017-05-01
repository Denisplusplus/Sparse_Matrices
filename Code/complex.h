#ifndef __COMPLEX_H__
#define __COMPLEX_H__


typedef struct {
     double a,b;
 } complex;

complex complex_divide(complex x, complex y);
double complex_absolute(complex x);
void complex_print(complex x);
int element_not_zero(complex x);
complex element_zero();
complex complexing(int row);
#endif
