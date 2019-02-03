/***********************************************
**********Spherical special Function************
***********************************************/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
/*Define besselj0(z) */
double besselj0(double x)
{
    return sin(x)/x;
}

/*Define besselj1(z) */
double besselj1(double x)
{
    return sin(x)/(x*x)-cos(x)/x;
}

/*Define besseljn(z) */
double besseljn(int n, double x)
{
    if (n==0) return besselj0(x);
    else if(n==1) return besselj1(x);
    /*using recurrence relation */
    else return (2*n-1)*besseljn(n-1,x)/x - besseljn(n-2,x);
}

/*Define derivative besseljn(z) by recurrence relation */
double dbesseljn(int n, double x)
{
	return - besseljn(n+1,x) + n*besseljn(n,x)/x;
}

/*Define nuemanny0(z) */
double nuemanny0(double x)
{
    return -cos(x)/x;
}

/*Define nuemanny1(z) */
double nuemanny1(double x)
{
    return -cos(x)/(x*x)-sin(x)/x;
}

/*Define nuemannyn(z) */
double nuemannyn(int n, double x)
{
    if (n==0) return nuemanny0(x);
    else if(n==1) return nuemanny1(x);
    /*using recurrence relation */
    else return ((2*n-1)*nuemannyn(n-1,x)/x-nuemannyn(n-2,x));
}

/*Define derivative nuemannyn(z) by recurrence relation */
double dnuemannyn(int n, double x)
{
	return - nuemannyn(n+1,x) + n*nuemannyn(n,x)/x;
}


int factorial(int n)
{
	if(n == 0) return 1;
	else return n*factorial(n-1);
}

/*Computes the associated Legendre polynomial P^m_n(x). 
Here m and n are integers satisfying 0 <= m <= n,1 <= x <= 1.*/
double original_legendre(int m, int n, double theta)
{
	m = abs(m);
	double fact,pll,pmm,pmmp1,somx2;
	int i,ll;
	double pi=3.141592653589793;
	double x = cos(theta*pi/180);
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
double gene_legendre(int m, int n, double theta)
{
	double plgdr;
	plgdr = original_legendre(m, n, theta);
	double frac = (double)factorial(n-abs(m));
	frac = frac/factorial(n+abs(m));
	printf("%d\n",frac);
	if (m >= 0) return plgdr*sqrt(frac*(2*n+1)/2);
	else 
	{
		m = abs(m);
		if(m%2 == 0)return plgdr*sqrt(frac*(2*n+1)/2);
		else return (-1)*plgdr*sqrt(frac*(2*n+1)/2);
	}
}

//Derivative legendre
double diff_legendre(int m, int n, double theta)
{
	double pi=3.141592653589793;
	double y, x;
	if(n == 0)
	{
		y = 0;
		return y;
	}
	x = cos(theta*pi/180);
	if(fabs(x*x-1) <= 1.0e-10) 
	{
		y = 0;
		return y;
	}
	else return (-(n+1)*x*original_legendre(m,n,theta)+(n-abs(m)+1)*original_legendre(m,n+1,theta))/(x*x-1.0);
}
