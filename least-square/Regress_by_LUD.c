//=======================================================================//
//This LU decomposition uses total pivoting to reduce the numerical error//
//=======================================================================//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i, j, k, f;	//for loop
	int m = 504, n = 15;	//for matrix
	int row, col, change_row[n] = {0}, change_col[n] = {0}, max[n] = {0}, maximum; // for find max

    //Loading files
	FILE *fp;
	float x[m], y[m], cd[m], A[m][n]; //for data
	double B[n][n] = {0}, Binv[n][n], L[n][n]; //inverse
	double temp = 0, d[n] = {0}, c[n] = {0}, z[n] = {0}, y_regres[m]; // for linear system
	fp = fopen("data.csv","r");
		if (fp == NULL) printf("data.txt does not exist\n");
		for (i=0; i<m; i++) fscanf(fp, "%f,%f,%f\n",&x[i] ,&y[i] ,&cd[i] );
	fclose(fp);
    //Loading files

    //Getting matrix A
	for(i=0; i<m; i++)
	{
		A[i][0] = 1;
		A[i][1] = x[i];
		A[i][2] = y[i];
		A[i][3] = x[i]*x[i];
		A[i][4] = x[i]*y[i];
		A[i][5] = y[i]*y[i];
		A[i][6] = x[i]*x[i]*x[i];
		A[i][7] = x[i]*x[i]*y[i];
		A[i][8] = x[i]*y[i]*y[i];
		A[i][9] = y[i]*y[i]*y[i];
		A[i][10] = x[i]*x[i]*x[i]*x[i];
		A[i][11] = x[i]*x[i]*x[i]*y[i];
		A[i][12] = x[i]*x[i]*y[i]*y[i];
		A[i][13] = x[i]*y[i]*y[i]*y[i];
		A[i][14] = y[i]*y[i]*y[i]*y[i];
		if(i < n) L[i][i] = 1.;
	}

    //Getting matrix B = A^T*A
	for(j=0; j<n; j++) for(i=0; i<m; i++) for(k=0; k<n; k++) B[j][k] = B[j][k] + A[i][j]*A[i][k];
    //Getting matrix B = A^T*A

	//Getting matrix B^-1

	//find the maximum value before (k-1)th times elimination of whole matrix
	for (k=0; k<n-1; k++)
	{
		for (f=k; f<n; f++)
		{
			for (j=0; j<n; j++)
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
			for (j=0; j<n; j++)
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

	//Find L (from I) and U (from B) matrix
		for (i=k+1; i<n; i++)
		{
			d[i] = B[i][col]/maximum;
			L[i][col] = d[i];
			for (j=0; j<n; j++)
			{
				if (d[i] != 0) B[i][j] = B[i][j] - B[k][j]*d[i];
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
		for (i=k+1; i<n; i++)
		{
			if(B[i][col] != 0) B[i][col] = B[i][col] - B[k][col]*B[i][col]/maximum;
		}
		maximum = 0;
	}
	//Find L (from I) and U (from B) matrix

	//permute L and U to triangles
	for(i=0; i<n; i++)
	{
		for(j=i; j<n; j++)
		{
			if(L[i][j] == 1.)
			{
				col = j;
				for(k=0; k<n; k++)
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

	//Forward substitute
	for(j=0; j<n; j++)
	{
		z[j] = 1;
		for(k=j+1; k<n; k++)
		{
			temp = 0.;
			for (i=0; i<k; i++) temp = temp - L[k][i]*z[i];
			z[k] = temp;
		}
	//Forward substitute

	//Backward substitute
		for (i=0; i<n; i++) max[i] = 0;
		c[n] = z[n]/B[n][n];
		for(k=n-1; k>-1; k--)
		{
			temp = 0.;
			for (i=k+1; i<n; i++) temp = temp - B[k][i]*c[i];
			c[k] = (z[k] + temp)/B[k][k];
		}
		for (i=0; i<n; i++) z[i] = 0;
	//Backward substitute
	for (i=0; i<n; i++) Binv[i][j] = c[i];
	}

	//permute
	for (k=j-1; k>-1; k--)
	{
		col = change_col[k];
		if(col != 0)
		{
			for (i=0; i<n; i++)
			{
				temp = Binv[i][col];
				Binv[i][col] = Binv[i][k];
				Binv[i][k] = temp;
			}
		}
	}

	for (k=j-1; k>-1; k--)
	{
		row = change_row[k];
		if(row != 0)
		{
			for (i=0; i<n; i++)
			{
				temp = Binv[row][i];
				Binv[row][i] = Binv[k][i];
				Binv[k][i] = temp;
			}
		}
	}
    //Getting matrix B^-1

    //Getting A^T*cd
	for (j=0; j<n; j++)
	{
		c[j] = 0;
		z[j] = 0;
	}
	for (i=0; i<m; i++) y_regres[i] = 0;

	for (j=0; j<n; j++) for (i=0; i<m; i++) c[j] = c[j] + A[i][j]*cd[i];
    //Getting A^T*cd
    //Getting B^-1*A^T*cd
	for (j=0; j<n; j++) for (i=0; i<n; i++) z[j] = z[j] + Binv[j][i]*c[i];
	for (j=0; j<n; j++) printf("%.16e\n", z[j]);
    //Getting A^T*y
    //Getting regressed y
	for (i=0; i<m; i++) for (j=0; j<n; j++) y_regres[i] = y_regres[i] + A[i][j]*z[j];
return 0;
}
