#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
double f(double x)
{
	return (x*x*x);
}

double simps(double y[], double x[], int n)
{
	int i;
	double h = x[1] - x[0], y1 = 0, y2 = 0, sum = 0;
	if (n < 2) sum = 0;
	else if (n == 2) sum = 0.5*h*(y[0]+y[1]);
	else if((n-1)%2 == 0)
	{
		for(i=1;i<n-1;i++)
		{
			if(i%2==0) y1 += y[i];
        	else y2 += y[i];
		}
		sum = h*(y[0]+2*y1+4*y2+y[n-1])/3;
	}
	else if((n-1)%3 == 0)
	{
		for(i=1;i<n-1;i++)
		{
			if(i%3==0) y1 += y[i];
        	else y2 += y[i];
		}
		sum = 3*h*(y[0]+2*y1+3*y2+y[n-1])/8;
	}
	else
	{
		for(i=1;i<n-4;i++)
		{
			if(i%2==0) y1 += y[i];
        	else y2 += y[i];
		}
		sum = h*(y[0]+2*y1+4*y2+y[n-4])/3 + 3*h*(y[n-4]+3*y[n-3]+3*y[n-2]+y[n-1])/8;
	}
	return sum;
}

int main(){
	//n is number of interval
	//a is lower limit
	//b is upper limit
	for(int n=2; n<20; n++)
	{
		int i;
		double *x, *y, h, a = 1.0, b = 4.0, z;
		h = (double)(b-a)/n;
		y = (double*)malloc((n+1)*sizeof(double));
		x = (double*)malloc((n+1)*sizeof(double));
		//n interval --> n+1 points
		for(i=0;i<n+1;i++)
		{
			x[i] = a + i*h;//For rectangular coordinate
			//x[i] = (a + i*h)*M_PI/180;//For polar coordinate
			z = x[i];
			y[i] = f(z);
			printf("%f\n",y[i]);
		}
		printf("sum = %f\n",simps(y,x,n+1));
		free(y);
		free(x);
	}
	return 0;
}
