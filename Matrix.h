#ifndef MATRIX_H
#define MATRIX_H

#include "NumAnalysis.h"
#define SIZE 10

struct matrix;
matrix O(int m, int n);
struct matrix
{
	int m, n;
	double mat[SIZE][SIZE];
	matrix(){}
	matrix(int n, int m){*this = O(m, n);}
	matrix(int n, int m, double a[SIZE][SIZE])
	{
		*this = O(m, n);
		for(int i = 0; i < m; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				mat[i][j] = a[i][j];
			}
		}
	}
};
matrix O(int m ,int n)
{
	matrix c;
	c.m = m;
	c.n = n;
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0 ;j < n; ++j)
		{
			c.mat[i][j] = 0;
		}
	}
	return c;
}
matrix add(matrix a, matrix b)
{
	matrix c = a;
	for(int i = 0 ;i < a.m; ++i)
	{
		for(int j = 0; j < a.n; ++j)
		{
			c.mat[i][j] = a.mat[i][j] + b.mat[i][j];
		}
	}
	return c;
}
matrix operator+(matrix a, matrix b)
{
	return add(a, b);
}
matrix sub(matrix a, matrix b)
{
	matrix c = a;
	for(int i = 0 ;i < a.m; ++i)
	{
		for(int j = 0; j < a.n; ++j)
		{
			c.mat[i][j] = a.mat[i][j] - b.mat[i][j];
		}
	}
	return c;
}
matrix operator-(matrix a, matrix b)
{
	return sub(a, b);
}
matrix mul(matrix a, matrix b)
{
	matrix c = O(a.m, b.n);
	for(int i = 0; i < c.m; ++i)
	{
		for(int j = 0; j < c.n; ++j)
		{
			for(int k = 0; k < a.n; ++k)
			{
				c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
			}
		}
	}
	return c;
}
matrix operator*(matrix a, matrix b)
{
	return mul(a, b);
}
matrix mul(matrix a, double b)
{
	matrix c = O(a.m, a.n);
	for(int i = 0; i < a.m; ++i)
	{
		for(int j = 0; j < a.n; ++j)
		{
			c.mat[i][j] = b * a.mat[i][j];
		}
	}
	return c;
}
matrix operator*(matrix a, double b)
{
	return mul(a, b);
}
matrix T(matrix a)
{
	matrix b(a.n, a.m);
	for(int i = 0; i < a.n; ++i)
	{
		for(int j = 0; j < a.m; ++j)
		{
			b.mat[i][j] = a.mat[j][i];
		}
	}
	return b;
}
double trace(matrix a)
{
	double tr = 0;
	for(int i = 0; i < a.n; ++i)
	{
		tr += a.mat[i][i];
	}
	return tr;
}
matrix last(matrix a, int i, int j)
{
	matrix m(a.m - 1, a.n - 1);
	int x = 0, y = 0;
	for(int p = 0; p < a.m; ++p)
	{
		for(int q = 0; q < a.n; ++q)
		{
			if(p == i || q == j)	continue;
			x = p;
			y = q;
			if(p > i)	x -= 1;
			if(q > j)	y -= 1;
			m.mat[x][y] = a.mat[p][q];
		}
	}
	return m;
}
double det(matrix a)
{
	if(a.n == 1)
		return a.mat[0][0];
	double ans = 0;
	for(int i = 0; i < a.n; ++i)
	{
		double sign = 1.0;
		if(i & 1)	sign -= 2.0;
		ans += a.mat[i][0] * det(last(a, i, 0)) * sign;
	}
	return ans;
}
double alglast(matrix a, int i, int j)
{
	double sign = 1.0;
	if((i + j) & 1)	sign -= 2.0;
	return det(last(a, i, j)) * sign;
}
matrix adj(matrix a)
{
	matrix adjm(a.m,a.n);
	for(int i = 0; i < a.m; ++i)
	{
		for(int j = 0; j < a.n; ++j)
		{
			adjm.mat[i][j] = alglast(a, j, i);
		}
	}
	return adjm;
} 
matrix inverse(matrix a)
{
	return mul(adj(a), 1.0 / det(a));
}
matrix rowk(matrix a, int row, double k)
{
	for(int i = 0; i < a.n; ++i)
	{
		a.mat[row][i] *= k; 
	}
	return a;
}
matrix swaprow(matrix a, int row1, int row2)
{
	for(int i = 0; i < a.n; ++i)
	{
		double temp = a.mat[row1][i];
		a.mat[row1][i] = a.mat[row2][i];
		a.mat[row2][i] = temp; 
	}
	return a;
}
matrix addproduct(matrix a, int row1, int row2, double k)
{
	for(int i = 0; i < a.n; ++i)
	{
		a.mat[row1][i] += a.mat[row2][i] * k;
	}
	return a;
}
void out(matrix c)
{
	for(int i = 0; i < c.m; ++i)
	{
		for(int j = 0; j < c.n; ++j)
		{
			printf("%lf ", c.mat[i][j]);
		}
		printf("\n");
	}
}
#endif
