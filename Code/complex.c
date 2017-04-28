#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "complex.h"

double complex_abs(complex x)
{
     return (hypot(x.a, x.b));
}

complex complex_divide(complex x, complex y)
{
	complex t;

	t.a = (x.a * y.a + x.b * y.b) / (y.a * y.a + y.b * y.b);
	t.b = (y.a * x.b - x.a * y.b) / (y.a * y.a + y.b * y.b);

	return t;
}

void complex_print(complex x)
{
	if (x.b < 0.0) {
		printf("%.1lf%.1lfi\n", x.a, x.b);
	} else {
		printf("%.1lf+%.1lfi\n", x.a, x.b);
	}
	
}
