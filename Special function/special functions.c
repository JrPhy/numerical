/***********************************************
**********Spherical special Function************
***********************************************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
/*Define besseljn(z) */
double Besseljn(int n, double x)
{
	int i;
	double besselj0, besselj1, besseljn;
	if(fabs(x)<1e-6) 
	{
		besselj0 = 1.0;
		besselj1 = 0.0;
	}
	else 
	{
		besselj0 = sin(x)/x;
		besselj1 = sin(x)/(x*x)-cos(x)/x;
	}
	if (n == 0) return besselj0;
	else if(n == 1) return besselj1;
	/*using recurrence relation */
	else 
	{
		if(fabs(x)<1e-6) besseljn = 0.0;
		else
		{
			for(i=2; i<n+1; i++) 
			{
				besseljn = (2*i-1)*besselj1/x - besselj0;
				besselj0 = besselj1;
				besselj1 = besseljn;
			}
		}
		return besseljn;
	} 
}

/*Define derivative besseljn(z) by recurrence relation */
double DiffBesseljn(int n, double x)
{
	return (-Besseljn(n+1,x) + n*Besseljn(n,x)/x);
}

/*Define Neumannyn(z) */
double Neumannyn(int n, double x)
{
	int i;
	double Neumanny0, Neumanny1, Neumannyn;
	Neumanny0 = (-cos(x)/x);
	Neumanny1 = (-cos(x)/(x*x)-sin(x)/x);
	if (n==0) return Neumanny0;
	else if(n==1) return Neumanny1;
	/*using recurrence relation */
	else 
	{
		for(i=2; i<n+1; i++) 
		{
			Neumannyn = (2*i-1)*Neumanny1/x - Neumanny0;
			Neumanny0 = Neumanny1;
			Neumanny1 = Neumannyn;
		}
	}
	return Neumannyn;
}

/*Define derivative nuemannyn(z) by recurrence relation */
double DiffNeumannyn(int n, double x)
{
	return - Neumannyn(n+1,x) + n*Neumannyn(n,x)/x;
}


int factorial(int n)
{
	int i, fact;
	if(n == 0) return 1;
	else 
	{
		fact = n;
		for(i=n; i>1; i--) fact = fact*(i-1);
	}
	return fact;
}

/*Computes the associated Legendre polynomial P^m_n(x). 
Here m and n are integers satisfying 0 <= m <= n,1 <= x <= 1.*/
double OriginalLegendre(int m, int n, double theta)
{
	m = abs(m);
	double fact,pll,pmm,pmmp1,somx2;
	int i,ll;
	double x = cos(theta*M_PI/180);
	if (m > n || fabs(x) > 1.0)
	{
		printf("%d	%d\n",m,n);
		printf("Bad arguments in routine PLGNDR\n");
		printf("correct arguments:\n");
		printf("0 <= m <= n,1 <= x <= 1");
		exit(1);
	}
	pmm=1.0;
	if (m > 0) 
	{
		somx2=sqrt((1.0-x)*(1.0+x));
		fact=1.0;
		for (i=1;i<=m;i++) 
		{
			pmm *= -fact*somx2;
			fact += 2.0;
		}
	}
	if (n == m) return pmm;
	else 
	{
		pmmp1=x*(2*m+1)*pmm;
		if (n == (m+1)) return pmmp1;
		else 
		{
			for (ll=(m+2);ll<=n;ll++) 
			{
				pll=(x*(2*ll-1)*pmmp1-(ll+m-1)*pmm)/(ll-m);
				pmm=pmmp1;
				pmmp1=pll;
			}
			return pll;
		}
	}
}

//General legendre
double GeneLegendre(int m, int n, double theta)
{
	double plgdr;
	plgdr = OriginalLegendre(m, n, theta);
	double frac = (double)factorial(n-abs(m));
	frac = frac/factorial(n+abs(m));
	printf("%f\n",frac);
	if (m >= 0) return plgdr*sqrt(frac*(2*n+1)/2);
	else 
	{
		m = abs(m);
		if(m%2 == 0)return plgdr*sqrt(frac*(2*n+1)/2);
		else return (-1)*plgdr*sqrt(frac*(2*n+1)/2);
	}
}

//Derivative legendre
double DiffLegendre(int m, int n, double theta)
{
	double y = 0, x = cos(theta*M_PI/180);
	if(n == 0) return y;
	if(fabs(x*x-1) <= 1.0e-10) return y;
	else return (-(n+1)*x*OriginalLegendre(m,n,theta)+(n-abs(m)+1)*OriginalLegendre(m,n+1,theta))/(x*x-1.0);
}

int main()
{
	int i, j;
	double x;
	for(j=0; j<10; j++) 
	{
		printf("%d\n",factorial(j));
		/*for(i=0; i<=180; i+=20) 
		{
			x = i*M_PI/180;
			printf("%f	%f\n",Neumannyn(j, x), Neumannyn(j, x));
		}
		printf("\n");*/
	}
	return 0;
}
