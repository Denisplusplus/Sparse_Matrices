#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "complex.h"

double complex_abs(complex x)
{
     return (hypot(x.re, x.im));
}

complex complex_divide(complex x, complex y)
{
	complex t;

	t.re = (x.re * y.re + x.im * y.im) / (y.re * y.re + y.im * y.im);
	t.im = (y.re * x.im - x.re * y.im) / (y.re * y.re + y.im * y.im);

	return t;
}

void complex_print(complex x)
{	
	if (x.im == 0.0) {
		printf("%.1lf\n", x.re);
	} else
	if (x.im < 0.0) {
		printf("%.1lf%.1lfi\n", x.re, x.im);
	} else {
		printf("%.1lf+%.1lfi\n", x.re, x.im);
	} 

	
}

int element_not_zero(complex x)
{
	if ((x.re != 0.0) && (x.im != 0.0)) {
		return 1;
	}
	return 0;

}

complex element_zero()
{
	complex x;
	x.re = 0.0;
	x.im = 0.0;
	return(x);
}

complex complexing(int row)
{
	complex x;
	x.re = (double)(row);
	x.im = 0.0;
	return x;
}

int equal(complex x, complex y)
{
	if ((x.re == y.re) && (x.im == y.im)) {
		return 1;
	}
	return 0;


}
