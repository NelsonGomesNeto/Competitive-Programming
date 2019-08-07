#include <bits/stdc++.h>
#define lli long long int
#define DEBUG if(0)
lli mod = 1e9 + 7;

void copyMatrix(lli f[2][2], lli a[2][2])
{
  for (int i = 0; i < 2; i ++)
    for (int j = 0; j < 2; j ++)
      f[i][j] = a[i][j];
}

void multiplyMatrix(lli a[2][2], lli b[2][2])
{
  lli aux[2][2]; memset(aux, 0, sizeof(aux));
  for (int i = 0; i < 2; i ++)
    for (int j = 0; j < 2; j ++)
      for (int k = 0; k < 2; k ++)
        aux[i][j] = (aux[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
  copyMatrix(a, aux);
}

void powerMatrix(lli matrix[2][2], lli n)
{
  lli aux[2][2] = {{1, 0}, {0, 1}};
  while (n)
  {
    if (n & 1) multiplyMatrix(aux, matrix);
    n /= 2;
    multiplyMatrix(matrix, matrix);
  }
  copyMatrix(matrix, aux);
}

lli brute(lli at, lli n)
{
  if (!n) return(!at);
  lli paths = 0;
  for (int i = 0; i < 4; i ++)
    if (at != i)
      paths += brute(i, n - 1);
  return(paths);
}

int main()
{
  int n; scanf("%d", &n); n = n > 1 ? n - 1 : 0;
  DEBUG for (int i = 1; i <= n; i ++) printf("%d - %lld\n", i, brute(0, i));

  lli base[2][2] = {{2, 3}, {1, 0}};
  powerMatrix(base, n);

  printf("%lld\n", base[0][1]);

  return(0);
}
/*
fibb: F(n) = F(n - 1) + F(n - 2)
1 1 F(n + 1) F(n)
1 0 F(n)     F(n - 1)
tetra: F(n) = 2*F(n - 1) + 3*F(n - 2)
2 3 F(n + 1) F(n)
1 0 F(n)     F(n - 1)
*/