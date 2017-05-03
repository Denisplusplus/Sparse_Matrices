#ifndef __COMPLEX_H__
#define __COMPLEX_H__


typedef struct {
     double re, im;
 } complex;

complex complex_divide(complex x, complex y);
double complex_abs(complex x);
void complex_print(complex x);
int element_not_zero(complex x);
int equal(complex x, complex y);
complex element_zero();
complex complexing(int row);
#endif
