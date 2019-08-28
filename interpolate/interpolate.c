#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void oneD_linear_intp(float* raw_1D, float* finegrid_1D, int column, int intp_col)
{
	intp_col +=1;
	float t, aa, bb;
	int x = 0, j;
	for(j=0; j<(column-1)*intp_col+1; j++)
	{
		if(j == 0) t = 0.0;
		else if(j%intp_col == 0) 
		{
			t = 1.0;
			x = (int)floor(j/intp_col) - 1;
		}
		else 
		{
			t = (float) (j%intp_col)/intp_col;
			x = (int)floor(j/intp_col);
		}
		aa = (1-t)*raw_1D[x];
		bb = t*raw_1D[x+1];
		finegrid_1D[j] = aa+bb;
	}
}

void twoD_linear_intp(float** raw_2D, float** finegrid_2D, int row, int column, int intp_col, int intp_row)
{
	if(row == 1||column == 1)
	{
		printf("please use 1D_linear_intp");
		exit(1);
	}
	intp_col +=1;
	intp_row +=1;
	float t, u, aa, bb, cc, dd;
	int x = 0, y = 0, i, j;
	for (i=0; i<(row-1)*intp_row+1; i++) 
	{
		if(i == 0) t = 0.0;
		else if(i%intp_row == 0) 
		{
			t = 1.0;
			y = (int)floor(i/intp_row) - 1;
		}
		else 
		{
			t = (float) (i%intp_row)/intp_row;
			y = (int)floor(i/intp_row);
		}
		x = 0;
		for(j=0; j<(column-1)*intp_col+1; j++)
		{
			if(j == 0) u = 0.0;
			else if(j%intp_col == 0) 
			{
				u = 1.0;
				x = (int)floor(j/intp_col) - 1;
			}
			else 
			{
				u = (float) (j%intp_col)/intp_col;
				x = (int)floor(j/intp_col);
			}
			aa = (1-t)*(1-u)*raw_2D[y][x];
			bb = t*(1-u)*raw_2D[y+1][x];
			cc = (1-t)*u*raw_2D[y][x+1];
			dd = t*u*raw_2D[y+1][x+1];
			finegrid_2D[i][j] = aa+bb+cc+dd;
		}
	}
}

double Langrange_intp(double *x, double *y, double intp_x, int n)
{
	int i, j;
	double a = 1.0, b = 1.0 ,intp_y = 0.0;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(i == j) continue;
			a *= intp_x - x[j];
			b *= x[j] - x[i];
		}
		intp_y += y[i]*a/b;
	}
	return intp_y;
}

int main(){
	int i, j, row = 2, column = 4, intp_col = 2, intp_row = 4;
    // 2D-Example
	float **raw_2D, **finegrid_2D;
    raw_2D = (float**)malloc(row*sizeof(float*));
    for(i=0; i<row; i++) raw_2D[i] = (float*)malloc(column*sizeof(float));
	for(i=0; i<row; i++) for(j=0; j<column; j++) raw_2D[i][j] = rand()%1000;
	finegrid_2D = (float**)malloc(((row-1)*(intp_row+1)+1)*sizeof(float*));
    for(i=0; i<(row-1)*(intp_row+1)+1; i++) finegrid_2D[i] = (float*)malloc(((column-1)*(intp_col+1)+1)*sizeof(float));
    twoD_linear_intp(raw_2D, finegrid_2D, row, column, intp_col, intp_row);
    for(i=0; i<row; i++) 
	{
		for(j=0; j<column; j++)
		{
			if(j == column-1) printf("%.1f\n",raw_2D[i][j]);
			else printf("%.1f	",raw_2D[i][j]);
			
		}	
	}
	printf("\n");
    for(i=0; i<(row-1)*(intp_row+1)+1; i++) 
	{
		for(j=0; j<(column-1)*(intp_col+1)+1; j++)
		{
			if(j == (column-1)*(intp_col+1)+1-1) printf("%.1f\n",finegrid_2D[i][j]);
			else printf("%.1f	",finegrid_2D[i][j]);
		}
	}
	for(i=0; i<row; i++) free(raw_2D[i]);
	free(raw_2D);
    for(i=0; i<(row-1)*(intp_row+1)+1; i++) free(finegrid_2D[i]);
    free(finegrid_2D);
    // 2D-Example
	// 1D-Example
    /*float *raw_1D, *finegrid_1D;
    raw_1D = (float*)malloc(column*sizeof(float));
    finegrid_1D = (float*)malloc(((column-1)*(intp_col+1)+1)*sizeof(float));
    for(j=0; j<column; j++) raw_1D[j] = rand()%1000;
    for(j=0; j<column; j++)
	{
		if(j == column-1) printf("%.1f\n",raw_1D[j]);
		else printf("%.1f	",raw_1D[j]);
	}
    oneD_linear_intp(raw_1D, finegrid_1D, column, intp_col);
    
    for(j=0; j<(column-1)*(intp_col+1)+1; j++)
	{
		if(j == (column-1)*(intp_col+1)+1-1) printf("%.1f\n",finegrid_1D[j]);
		else printf("%.1f	",finegrid_1D[j]);
	}
    free(raw_1D);
    free(finegrid_1D);*/
    // 1D-Example
    
    return 0;
}
