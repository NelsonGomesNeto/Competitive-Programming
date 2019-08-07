#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int
lli mod = 1e4, n, l;
lli matrixGraph[(int) 1e2][(int) 1e2];

void printMatrix(lli m[(int) 1e2][(int) 1e2])
{
  DEBUG for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++)
    printf("%lld%c", m[i][j], j < n - 1 ? ' ' : '\n');
}

void multiplyMatrix(lli a[(int) 1e2][(int) 1e2], lli b[(int) 1e2][(int) 1e2])
{
  lli aux[(int) 1e2][(int) 1e2]; memset(aux, 0, sizeof(aux));
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      for (int k = 0; k < n; k ++)
        aux[i][j] = (aux[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++)
    a[i][j] = aux[i][j];
}

void powerMatrix(lli t)
{
  lli aux[(int) 1e2][(int) 1e2];
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++)
    aux[i][j] = i == j;
  while (t)
  {
    if (t & 1) multiplyMatrix(aux, matrixGraph);
    t /= 2;
    multiplyMatrix(matrixGraph, matrixGraph);
  }
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++)
    matrixGraph[i][j] = aux[i][j];
}

int main()
{
  while (scanf("%lld %lld", &n, &l) != EOF)
  {
    memset(matrixGraph, 0, sizeof(matrixGraph));
    int s, t; scanf("%d %d", &s, &t); s --; t --;
    vector<int> graph[n]; int u;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < 4; j ++)
      {
        scanf("%d", &u); u --;
        graph[i].push_back(u);
      }

    for (int i = 0; i < n; i ++)
      for (auto j: graph[i])
        matrixGraph[i][j] ++;

    powerMatrix(l);
    DEBUG printMatrix(matrixGraph);
    printf("%lld\n", matrixGraph[s][t]);
    DEBUG printf("\n");
  }
  return(0);
}