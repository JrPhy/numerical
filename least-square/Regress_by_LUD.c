//=======================================================================//
//This LU decomposition uses total pivoting to reduce the numerical error//
//=======================================================================//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void swap(double* a, double* b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

void inverseByPLUD(int m, int n, double A[][n], double B[][n], double Binv[][n])
{
    int i, j, k, f;	//for loop
    int row, col, change_row[n], change_col[n];
    double temp, L[n][n], max[n], d[n], maximum = 0, c[n], z[n], y_regres[m], minimum = 999;

    for(i=0; i<n; i++)
	{
		max[i] = 0.;
		d[i] = 0.;
		L[i][i] = 1.;
		for (j=i+1; j<n; j++)
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
	for(k=0; k<n-1; k++)
	{
		for(f=k; f<n; f++)
		{
			max[f] = 0;
			for(j=0; j<n; j++)
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
			for(j=0; j<n; j++)
			{
				swap(&B[row][j], &B[k][j]);
				swap(&L[row][j], &L[k][j]);

				change_row[k] = row;
			}
		}
        //Choosing the pivot
        //Find L and U matrix
		for(i=k+1; i<n; i++)
		{
			d[i] = B[i][col]/maximum;
			L[i][col] = d[i];
			for(j=0; j<n; j++)
			{
				if(d[i] != 0)
				{
					B[i][j] = B[i][j] - B[k][j]*d[i];
				}
				else
				{
					swap(&L[k][j], &L[k+1][j]);
					swap(&B[k][j], &B[k+1][j]);
				}
			}
		}
		for(i=k+1; i<n; i++)
		{
			if(B[i][col] != 0)
			{
				B[i][col] = B[i][col] - B[k][col]*B[i][col]/maximum;
			}
		}
		maximum = 0;
	}
	//Find L and U matrix

	//permute L and U to triangles
	for(i=0; i<n; i++)
	{
		for(j=i; j<n; j++)
		{
			if(fabs(L[i][j]-1.) < 1e-6 )
			{
				col = j;
				for(k=0; k<n; k++)
				{
					swap(&B[k][i], &B[k][col]);
					swap(&L[k][i], &L[k][col]);
				}
			}
		}
		change_col[i] = col;
	}
	/*
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
		    if(j == n-1) printf("%.3e\n", B[i][j]);
		    else printf("%.3e  ", B[i][j]);
		}
	}
	*/
	//permute to upper and lower triangles
	//Forward subtitute
	for(j=0; j<n; j++)
	{
		z[j] = 1;
		for(k=j+1; k<n; k++)
		{
			temp = 0.;
			for (i=0; i<k; i++)
			{
				temp = temp - L[k][i]*z[i];
			}
			z[k] = temp;
		}
	//Forward subtitute
	//Backward subtitute
		for (i=0; i<n; i++) max[i] = 0;
		c[n] = z[n]/B[n][n];
		for(k=n-1; k>=0; k--)
		{
			temp = 0.;
			for (i=k+1; i<n; i++)
			{
				temp = temp - B[k][i]*c[i];
			}
			c[k] = (z[k] + temp)/B[k][k];
		}
		for (i=0; i<n; i++) z[i] = 0;
	//Backward subtitute
		for (i=0; i<n; i++) Binv[i][j] = c[i];
	}
	//permute
	for (k=j-1; k>=0; k--)
	{
		col = change_col[k];
		if(col != 0)
		{
			for (i=0; i<n; i++)
			{
			    swap(&Binv[i][col], &Binv[i][k]);
			}
		}
	}

	for (k=j-1; k>=0; k--)
	{
		row = change_row[k];
		if(row != 0)
		{
			for (i=0; i<n; i++)
			{
				swap(&Binv[row][i], &Binv[k][i]);
			}
		}
	}
}

int main() {
	int i, j, k, f;	//for loop
	int m = 504, n = 15;	//for matrix
	int row, col, change_row[n], change_col[n];
//Loading files
	FILE *fp;
	float x[m], y[m], cd[m];
	double A[m][n], B[n][n], Binv[n][n];
	double maximum = 0, c[n], z[n], y_regres[m], minimum = 999;
	fp = fopen("data.txt","r");
		if (fp == NULL) printf("data does not exist\n");
		for (i=0; i<m; i++) fscanf(fp, "%f	%f	%f\n",&x[i] ,&y[i] ,&cd[i] );
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
	}
//Getting matrix A
//Getting matrix B = A^T*A
	for(j=0; j<n; j++)
	{
		for(k=0; k<n; k++)
		{
		    B[j][k] = 0.;
		    Binv[j][k] = 0.;
		}
		c[j] = 0;
		z[j] = 0;
	}
	for(j=0; j<n; j++) for(i=0; i<m; i++) for(k=0; k<n; k++) B[j][k] = B[j][k] + A[i][j]*A[i][k];
//Getting matrix B = A^T*A
//Getting matrix B^-1
	inverseByPLUD(m, n, A, B, Binv);
//Getting A^T*cd
	for (i=0; i<m; i++) y_regres[i] = 0;
	for (j=0; j<n; j++) for (i=0; i<m; i++) c[j] = c[j] + A[i][j]*cd[i];
//Getting A^T*cd
//Getting B^-1*A^T*cd
	for (j=0; j<n; j++) for (i=0; i<n; i++) z[j] = z[j] + Binv[j][i]*c[i];
	fp = fopen("coefficients.txt","w");
	for (j=0; j<n; j++) fprintf(fp, "%.16e\n", z[j]);
	fclose(fp);
//Getting A^T*cd
//Getting y_regres
	for(i=0; i<m; i++) for (j=0; j<n; j++) y_regres[i] = y_regres[i] + A[i][j]*z[j];
	return 0;
}
