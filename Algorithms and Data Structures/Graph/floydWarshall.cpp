#include <bits/stdc++.h>
using namespace std;

const int maxVertices = 1e3, inf = 1e7; int n, m;

void printMatrix(int mat[maxVertices][maxVertices])
{
  printf("    | "); for (int i = 0; i < n; i ++) printf("%3d%c", i, i < n - 1 ? ' ' : '\n');
  printf("    | "); for (int i = 0; i < n; i ++) printf("---%c", i < n - 1 ? '-' : '\n');
  for (int i = 0; i < n; i ++)
  {
    printf("%3d | ", i);
    for (int j = 0; j < n; j ++)
      printf("%3d%c", mat[i][j], j < n - 1 ? ' ' : '\n');
  }
}

int dist[maxVertices][maxVertices], nxt[maxVertices][maxVertices], edges[maxVertices][maxVertices];
void floydWarshall()
{
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      if (i == j) dist[i][j] = 0;
      else if (edges[i][j] != -1) dist[i][j] = edges[i][j], nxt[i][j] = j;
      else dist[i][j] = inf;

  for (int k = 0; k < n; k ++)
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j], nxt[i][j] = nxt[i][k];
}

int main()
{
  memset(edges, -1, sizeof(edges)); memset(nxt, -1, sizeof(nxt));
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v, c; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &c); u --, v --;
    edges[u][v] = edges[v][u] = c;
  }

  floydWarshall();
  printf("\tDistance Matrix:\n"); printMatrix(dist);
  printf("\tNext Matrix:\n"); printMatrix(nxt);
}