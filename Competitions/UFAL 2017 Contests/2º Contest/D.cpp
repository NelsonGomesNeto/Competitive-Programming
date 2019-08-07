#include <bits/stdc++.h>
#define lli long long int
lli mod = 1e9 + 7;

void multiplyMatrix(lli a[4][4], lli b[4][4])
{
  lli aux[4][4]; memset(aux, 0, sizeof(aux));
  for (int i = 0; i < 4; i ++)
    for (int j = 0; j < 4; j ++)
      for (int k = 0; k < 4; k ++)
        aux[i][j] = (aux[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
  for (int i = 0; i < 4; i ++)
    for (int j = 0; j < 4; j ++)
      a[i][j] = aux[i][j];
}

void powerMatrix(lli graph[4][4], int n)
{
  lli res[4][4];
  for (int i = 0; i < 4; i ++)
    for (int j = 0; j < 4; j ++)
      res[i][j] = i == j;
  while (n > 0)
  {
    if (n & 1) multiplyMatrix(res, graph);
    n /= 2;
    multiplyMatrix(graph, graph);
  }
  for (int i = 0; i < 4; i ++)
    for (int j = 0; j < 4; j ++)
      graph[i][j] = res[i][j];
}

int main()
{
  int n; scanf("%d", &n);
  lli graph[4][4];
  for (int i = 0; i < 4; i ++)
    for (int j = 0; j < 4; j ++)
      graph[i][j] = i != j;

  powerMatrix(graph, n);
  printf("%lld\n", graph[3][3] % mod);

  return(0);
}

/*
Graph:
  A B C D
A 0 1 1 1
B 1 0 1 1
C 1 1 0 1
D 1 1 1 0
*/