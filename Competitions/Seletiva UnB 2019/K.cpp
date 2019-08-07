#include <bits/stdc++.h>
using namespace std;

const int maxN = 100;
int n, u, f, m;
long double matrix[maxN][maxN], pp[maxN][maxN];
void printMat(long double mat[maxN][maxN])
{
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      printf("%8.3Lf%c", mat[i][j], j < n - 1 ? ' ' : '\n');
}
void wolf(long double mat[maxN][maxN])
{
  printf("{");
  for (int i = 0; i < n; i ++)
  {
    printf("{");
    for (int j = 0; j < n; j ++) printf("%.3Lf%c", mat[i][j], j < n - 1 ? ',' : '}');
    if (i < n - 1) printf(",");
  }
  printf("}\n");
}

void matrixMult(long double a[maxN][maxN], long double b[maxN][maxN])
{
  long double res[maxN][maxN]; for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) res[i][j] = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      for (int k = 0; k < n; k ++)
        res[i][j] += a[i][k] * b[k][j];
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) a[i][j] = res[i][j];
}

int main()
{
  scanf("%d %d %d %d", &n, &u, &f, &m);
  long double p = 0;
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) scanf("%Lf", &matrix[i][j]), pp[i][j] = 0;

  for (int j = 0; j < n; j ++) pp[u][j] = matrix[u][j];

  for (int j = 1; j < m; j ++)
  {
    for (int i = 0; i < n; i ++) pp[i][f] = 0;
    matrixMult(pp, matrix);
  }
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) if (j != f) p += pp[i][j];
  if (m == 0) printf("1.0\n");
  else printf("%.15Lf\n", p);

  return(0);
}