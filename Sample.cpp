#include "cna.h"
#define H 1e-6
void invDLU(matrix a, matrix &d, matrix &l, matrix &u)
{
	for(int i = 0; i < a.m; ++i)
	{
		for(int j = 0; j < a.n; ++j)
		{
			if(i == j)
			{
				d.mat[i][j] = 1.0 / a.mat[i][j];
			}
			if(i < j)
			{
				u.mat[i][j] = a.mat[i][j];
			}
			if(i > j)
			{
				l.mat[i][j] = a.mat[i][j];
			} 
		}
	}
}
int main()
{
	double mt1[SIZE][SIZE] = 
	{
		{1.1, 3.1, 3.4, 1.9}, 
		{7.0, 2.7, 6.5, 8.7},
		{4.0, 3.3, 4.1, 9.7},
		{1.4, 5.6, 1.2, 3.8},
	};
	double mt2[SIZE][SIZE] = 
	{
		{1.2, 3.7, 4.4, 1.9}, 
		{7.1, 4.7, 2.5, 3.7},
		{4.1, 3.1, 6.2, 9.3},
		{1.6, 5.7, 2.2, 6.8},
	};
	matrix a(4, 4, mt1), b(4, 4, mt2);
	printf("a=\n");
	out(a);
	printf("b=\n");
	out(b);
	printf("a x b = \n");
	out(mul(a, b));
	printf("b x a = \n");
	out(mul(b, a));
	printf("tr[a] = %lf\n", trace(a));
	printf("tr[b] = %lf\n", trace(b));
	printf("a^T = \n");
	out(T(a));
	printf("b^T = \n");
	out(T(b));
	printf("det(a) = %lf\n", det(a));
	printf("det(b) = %lf\n", det(b));
	printf("adj(a) = \n");
	out(adj(a));
	printf("adj(b) = \n");
	out(adj(b));
	printf("a^-1 = \n");
	out(inverse(a));
	printf("b^-1 = \n");
	out(inverse(b));
	matrix d(a.m, a.n), l(a.m, a.n), u(a.m, a.n);
	printf("D^-1 = \n");
	invDLU(a, d, l, u);
	out(d);
	printf("L = \n");
	out(l);
	printf("U = \n");
	out(u);
	return 0;
}
