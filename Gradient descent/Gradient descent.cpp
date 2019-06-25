#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double function(double x)
{
	return x*x - 4*x+2;
}
//the function can only be 1-dimension
double dfx(double x0, double x1)
{
	return (function(x1) - function(x0))/(x1-x0);
}

double GD(double x0, unsigned int max_iters, double lambda, double error)
{
	double x1 = x0 + 0.1;
	unsigned int iters = 0;
	double temp,c_error = error+1;
	while(error < c_error && iters < max_iters)
	{
		temp = x1;
		x1 -= dfx(temp, x0) * lambda;
		c_error = fabs(x1-temp);
		printf("\nc_error %f\n", c_error);
		iters++;
		x0 = temp;
	}
    printf("\n iterators times %d\n", iters);
    return x1;
}

int main() {
	double x0 = 10, x1;
	double error = 1e-6, lambda = 0.1;
	unsigned int max_iters = 10000;
	x1 = GD(x0, max_iters, lambda, error);
	printf("The local minimum is: %f, The value is: %f\n", x1,function(x1));
	return 0;
}
