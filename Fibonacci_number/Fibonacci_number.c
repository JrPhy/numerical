#include<stdio.h> 

int Fibonacci(int n)
{
	if (n == 0) return 0;
	else if( n == 2 || n == 1) return 1;
	else
	{
		int fzero, fone, ftwo, i;
		fzero = 1;
		fone = 1;
		for(i=2;i<n;i++) 
		{
			ftwo = fone + fzero;
			fzero = fone;
			fone = ftwo;
		}
		return ftwo;
	}
}

int main()
{
	int i;
	for(i=0; i<15; i++) printf("%d	%d\n",i,Fibonacci(i));
}
