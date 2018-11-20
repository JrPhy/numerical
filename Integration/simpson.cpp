#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
int main(){
	int i, a = 0, b = 1;
	double g[n+1], h, y1 = 0, y2 = 0, sum = 0;
	h = (double)(b-a)/n;
	for(i=0; i<n+1; i++) g[i] = exp(i*h);
	if(n%2 == 0)
	{
		for(i=1;i<n;i++)
		{
			if(i%2==0) y1 += g[i];
        	else y2 += g[i];
		}
		sum = h*(g[0]+2*y1+4*y2+g[n])/3;
	}
	else if(n%3 == 0)
	{
		for(i=1;i<n;i++)
		{
			if(i%3==0) 	y1 += g[i];
        	else y2 += g[i];
		}
		sum = 3*h*(g[0]+2*y1+3*y2+g[n])/8;
	}
	else
	{
		for(i=1;i<n-3;i++)
		{
			if(i%2==0) y1 += g[i];
        	else y2 += g[i];
		}
		sum = h*(g[0]+2*y1+4*y2+g[n-3])/3 + 3*h*(g[n-3]+3*g[n-2]+3*g[n-1]+g[n])/8;
	}
return 0;
}