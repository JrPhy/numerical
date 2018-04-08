//=============================================================================//
// This program uses LU decomposition to solve the Least-square problem        //
// Copy all elements of the matirx from excel and paste in "A_matrix.txt" file //
// then this program will output the coefficients in "coefficients.txt"        //
//=============================================================================//
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;

int main() {
	int i, j, k;	//for loop
	int m, n;	//for matrix
	
	printf("How many coulums?\n");
	scanf("%d", &m);
	printf("How many rows?\n");
	scanf("%d", &n);
	printf("A is %d by %d matrix\n", m, n);

//Loading files
	FILE *fp;
	double A[m+1][n+1], B[n+1][n+1], data[n+1];
	double L[n+1][n+1], temp, d[n+1], c[n+1], z[n+1], Binv[n+1][n+1];
	fp = fopen("data.txt","r");
		if (fp == NULL) printf("A_matrix doesn't exist\n");
		for (i=1; i<m+1; i++) for (j=1; j<n+1; j++) fscanf(fp, "%lf\n",&A[i][j]);
	fclose(fp);
//Loading files
//Getting matrix B = A^T*A
	for(j=1; j<n+1; j++) for(k=1; k<n+1; k++) B[j][k] = 0;
	for(j=1; j<n+1; j++) for(i=1; i<m+1; i++) for(k=1; k<n+1; k++) B[j][k] = B[j][k] + A[i][j]*A[i][k];
//Getting matrix B = A^T*A
//Getting matrix B^-1
	for(i=1; i<n+1; i++)
	{
		d[i] = 0.;
		L[i][i] = 1.;
		for (j=i+1; j<n+1; j++)
		{
			L[i][j] = 0.;
			L[j][i] = 0.;
		}
		c[i] = 0.;
		z[i] = 0.;
	}	
	//Find L(from I) and U(from B) matrix
	for (i=k+1; i<n+1; i++) 
	{	
		d[i] = B[i][j]/B[i][i];
		for (j=1; j<n+1; j++) 
		{	
			if (d[i] != 0)
			{
				B[i][j] = B[i][j] - B[k][j]*d[i]; 
			}
			else
			{
				temp = L[k][j];
				L[k][j] = L[k+1][j];
				L[k+1][j] = temp;
				temp = B[k][j];
				B[k][j] = B[k+1][j];
				B[k+1][j] = temp;
			}
		}
	}
	//Find L(from I) and U(from B) matrix
	//Forward subtitute
	for(j=1; j<n+1; j++)
	{
		z[j] = 1;
		for(k=j+1; k<n+1; k++)
		{
			temp = 0.;
			for (i=1; i<k; i++)
			{
				temp = temp - L[k][i]*z[i];
			}
			z[k] = temp;
		}
	//Forward subtitute
	//Backward subtitute
		c[n] = z[n]/B[n][n];
		for(k=n-1; k>0; k--)
		{
			temp = 0.;
			for (i=k+1; i<n+1; i++)
			{
				temp = temp - B[k][i]*c[i];
			}
			c[k] = (z[k] + temp)/B[k][k];
		}
		for (i=1; i<n+1; i++) z[i] = 0;
	}
	//Backward subtitute	
//Getting matrix B^-1	
//Getting A^T*cd
	for (j=1; j<n+1; j++)
	{
		c[j] = 0;
		z[j] = 0;
	}
	
	for (j=1; j<n+1; j++) for (i=1; i<m+1; i++) c[j] = c[j] + A[i][j]*data[j];
//Getting A^T*cd
//Getting B^-1*A^T*cd
	for (j=1; j<n+1; j++) for (i=1; i<n+1; i++) z[j] = z[j] + Binv[j][i]*c[i];
//Getting B^-1*A^T*cd
	fp = fopen("coefficients.txt","w");
	for (i=1; i<n+1; i++) fprintf(fp, "%.16f\n", z[i]);
	fclose(fp);
	printf("coefficients.txt print successfully.\n");
	printf("Press any key to close the windows.\n");
	system ("PAUSE");
return 0;
}
