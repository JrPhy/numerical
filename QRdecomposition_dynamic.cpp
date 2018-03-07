//=============================================================================//
// This program uses QR decomposition to solve the Least-square problem        //
// Copy all elements of the matirx from excel and paste in "A_matrix.txt" file //
// then this program will output the coefficients in "coefficients.txt"        //
//=============================================================================//
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 

using namespace std;

int main() {
	int i, j, k, h, m, n; //for loop
	
	printf("How many coulums?\n");
	scanf("%d", &m);
	printf("How many rows?\n");
	scanf("%d", &n);
	printf("A is %d by %d matrix\n", m, n);
	
	double **A, **I, **R, ***H;
	A = (double**)malloc((m+1)*sizeof(double*));//Input matrix
	I = (double**)calloc(m+1, sizeof(double*));	//for Identity matrix
	R = (double**)calloc(m+1, sizeof(double*));	//
	H = (double***)calloc(n+1, sizeof(double**));
	for(k=0; k<n+1; k++) H[k] = (double**)calloc(m+1, sizeof(double*));
	
	fp = fopen("A.txt","r");
		if (fp == NULL) printf("AÀÉ®×¶}±Ò¥¢±Ñ\n");
		for (i=1; i<m+1; i++) for(j=1; j<n+1; j++) fscanf(fp, "%lf	",&A[i][j]);
	fclose(fp);

	// Creating I_m
	for (i=1; i<m+1; i++) 
	{
		I[i][i] = 1.;
		for (j=i+1; j<m+1; j++)
		{
			I[i][j] = 0.;
			I[j][i] = 0.;
		}
	}
	
	for (k=1; k<n+1; k++) 
	{
		for (i=1; i<m+1; i++) H[k][i][i] = 1.;
		c[k] = 0;
		z[k] = 0;
	}
	// Creating I_m
	// QR Decomposition
	for (k=1; k<n+1; k++) 
	{
		norm = 0.;
		for (i=k; i<m+1; i++) 
		{
			u[i] = A[i][k];
			norm = norm + u[i]*u[i];
		}
		norm = pow(norm,0.5);
		u[k] = u[k] + norm;
		norm = 0.;
		
		for (i=k; i<m+1; i++) norm = norm + u[i]*u[i];
		
		for (i=k; i<m+1; i++) for (j=k; j<m+1; j++) H[k][i][j] = I[i][j] - 2*u[i]*u[j]/norm;
		
		for (i=k; i<m+1; i++) for (j=k; j<m+1; j++) for (h=k; h<n+1; h++) R[i][h] = R[i][h] + H[k][i][j]*A[j][h];
		
		for (i=k; i<m+1; i++) 
		{
			for (j=k; j<n+1; j++) 
			{
				A[i][j] = R[i][j];
				R[i][j] = 0.;
			}
		}
	}
		
	for (k=1; k<n; k++)
	{
		for (i=1; i<m+1; i++) for (j=1; j<m+1; j++) for (h=1; h<m+1; h++) H[0][i][h] = H[0][i][h] + H[k][i][j]*H[k+1][j][h];
	
		for (i=1; i<m+1; i++) 
		{
			for (j=1; j<m+1; j++) 
			{
				H[k+1][i][j] = H[0][i][j];
				H[0][i][j] = 0.;
			}
			for (j=1; j<n+1; j++) R[i][j] = 0.;
		}
		for (i=k+1; i<n+1; i++) A[i][k] = 0.;
	}
	// QR Decomposition
	// H[n][i][j] = Q[i][j]
	// A^T*cd
	for (i=1; i<n+1; i++) for (j=1; j<m+1; j++) z[i] = z[i] + H[n][j][i]*cd[j];
	// A^T*cd
	//Backward subtitute
	c[n] = z[n]/A[n][n];
	for(j=1; j<n+1; j++)
	{
		for(k=n-1; k>0; k--)
		{
			temp = 0.;
			for (i=k+1; i<n+1; i++)
			{
				temp = temp - A[k][i]*c[i];
			}
			c[k] = (z[k] + temp)/A[k][k];
		}
	}	
	//Backward subtitute	
	fp = fopen("coefficients.txt","w");
	for (i=1; i<n+1; i++) fprintf(fp, "%.16f\n", z[i]);
	fclose(fp);

	for(k=0; k<n+1; k++) for(i=0; i<m+1; i++) free(H[k][i]);
	for(i=0; i<m+1; i++)
	{
		free(I[i]);
		free(A[i]);
	}
	for(i=0; i<n+1; i++) 
	{	
		free(H[i]);
		free(R[i]);
	}
	free(H);
	free(I);
	free(R);
	free(A);
	free(x);
	free(y);
	free(cd);
	printf("CDLLS.txt create successfully\n");
	printf("Press any key to close the windows.\n");
	system ("PAUSE");
	return 0;
}
	
