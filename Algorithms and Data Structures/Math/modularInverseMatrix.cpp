#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const lli mod = 13;
const int maxN = 100, maxM = 100, inf = 1e9; int an, am, bn, bm;
lli A[maxN][maxM], inverse[maxN][maxM], B[maxN][maxM];

void printMatrix(lli a[maxN][maxM], int n, int m)
{
  int size = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
    {
      int aux = a[i][j], s = a[i][j] == 0;
      while (aux) aux /= 10, s ++;
      size = max(size, s);
    }
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      printf("%*lld%c", size, a[i][j], j < m - 1 ? ' ' : '\n');
}

void switchLines(lli a[maxN][maxM], int i, int l, int m)
{
  for (int k = 0; k < m; k ++)
    swap(a[i][k], a[l][k]);
}

void subLine(lli a[maxN][maxM], int i, int j, lli c, int m)
{
  for (int k = 0; k < m; k ++)
    a[j][k] = (a[j][k] - (c * a[i][k]) % mod) % mod;
}

void multLine(lli a[maxN][maxM], int i, lli c, int m)
{
  for (int k = 0; k < m; k ++)
    a[i][k] = (a[i][k] * c) % mod;
}

int gaussElimination(lli a[maxN][maxM], lli inv[maxN][maxM], lli b[maxN][maxM])
{
  for (int i = 0, l; i < min(an, am); i ++)
  {
    for (l = i; l < an && a[l][i] == 0; l ++);
    if (l == an) break;
    switchLines(a, i, l, am), switchLines(inv, i, l, am), switchLines(b, i, l, bm);
    for (int j = 0; j < an; j ++)
    {
      if (i == j) continue;
      if (a[j][i] < 0) multLine(a, j, -1, am), multLine(inv, j, -1, am), multLine(b, j, -1, bm);
      if (a[i][i] < 0) multLine(a, i, -1, am), multLine(inv, i, -1, am), multLine(b, i, -1, bm);
      lli c, r = 1, p = a[j][i], q = a[i][i];
      while (r)
      {
        c = p / q, r = p % q;
        subLine(a, i, j, c, am), subLine(inv, i, j, c, am), subLine(b, i, j, c, bm);
        p = q; q = r;
      }
    }
  }
}

int main()
{
  scanf("%d %d", &an, &am);
  for (int i = 0; i < an; i ++)
  {
    inverse[i][i] = 1;
    for (int j = 0; j < am; j ++)
      scanf("%lld", &A[i][j]);
  }
  scanf("%d %d", &bn, &bm);
  for (int i = 0; i < bn; i ++)
    for (int j = 0; j < bm; j ++)
      scanf("%lld", &B[i][j]);

  printf("Solutions: %d\n", gaussElimination(A, inverse, B));
  printf("A:\n");
  printMatrix(A, an, am);
  printf("B:\n");
  printMatrix(B, bn, bm);
  printf("inverse:\n");
  printMatrix(inverse, am, an);

  return(0);
}