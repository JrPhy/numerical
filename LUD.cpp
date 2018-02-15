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
	int i, j, k, f;	//for loop
	int m, n;	//for matrix
	
	printf("How many coulums?\n");
	scanf("%d", &m);
	printf("How many rows?\n");
	scanf("%d", &n);
	printf("A is %d by %d matrix\n", m, n);
	
	int row, col, change_row[n+1], change_col[n+1];
//Loading files
	FILE *fp;
	double A[m+1][n+1], B[n+1][n+1], data[n+1];
	double L[n+1][n+1], temp, max[n+1], d[n+1], maximum, c[n+1], z[n+1], Binv[n+1][n+1];
	fp = fopen("A_matrix.txt","r");
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
		max[i] = 0.;
		d[i] = 0.;
		L[i][i] = 1.;
		for (j=i+1; j<n+1; j++)
		{
			L[i][j] = 0.;
			L[j][i] = 0.;
		}
		change_row[i] = 0;
		change_col[i] = 0;
		c[i] = 0.;
		z[i] = 0.;
	}	
	//find the maximum value before (k-1)th times elimination of whole matrix
	for (k=1; k<n; k++)
	{
	
		for (f=k; f<n+1; f++)
		{
			max[f] = 0;
			for (j=1; j<n+1; j++)
			{
				if(fabs(B[f][j]) > fabs(max[f])) max[f] = B[f][j];	
				if(fabs(B[f][j]) > fabs(maximum)) 
				{
					maximum = B[f][j];
					row = f;
					col = j; 
				}	
			}
		}
	//find the maximum value before (k-1)th times elimination of whole matrix
	//Choosing the pivot
		if(fabs(max[k]) < fabs(B[row][col]))
		{		
			for (j=1; j<n+1; j++)
			{
				temp = B[row][j];
				B[row][j] = B[k][j];
				B[k][j] = temp;

				temp = L[row][j];
				L[row][j] = L[k][j];
				L[k][j] = temp;
				
				change_row[k] = row;
			}
		}
	//Choosing the pivot
	//Find L(from I) and U(from B) matrix
		for (i=k+1; i<n+1; i++) 
		{	
			d[i] = B[i][col]/maximum;
			L[i][col] = d[i];
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
		for (i=k+1; i<n+1; i++)
		{
			if(B[i][col] != 0)
			{
				B[i][col] = B[i][col] - B[k][col]*B[i][col]/maximum;
			}
		}
		maximum = 0;
	}
	//Find L(from I) and U(from B) matrix
	//permute L and U to triangles
	for(i=1; i<n+1; i++)
	{
		for(j=i; j<n+1; j++)
		{
			if(L[i][j] == 1.) 
			{
				col = j;
				for(k=1; k<n+1; k++)
				{
					temp = B[k][i];
					B[k][i] = B[k][col];
					B[k][col] = temp;

					temp = L[k][i];
					L[k][i] = L[k][col];
					L[k][col] = temp;
				}
			}
		}
		change_col[i] = col;
	}
	//permute to upper and lower triangles
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
	//Backward subtitute	
		for (i=1; i<n+1; i++) Binv[i][j] = c[i];
	}
	//permute
	for (k=j-1; k>0; k--)
	{
		col = change_col[k];
		if(col != 0)
		{
			for (i=1; i<n+1; i++)
			{
				temp = Binv[i][col];
				Binv[i][col] = Binv[i][k];
				Binv[i][k] = temp;
			}
		}
	}
	
	for (k=j-1; k>0; k--)
	{
		row = change_row[k];
		if(row != 0)
		{
			for (i=1; i<n+1; i++)
			{
				temp = Binv[row][i];
				Binv[row][i] = Binv[k][i];
				Binv[k][i] = temp;
			}
		}
	}
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
