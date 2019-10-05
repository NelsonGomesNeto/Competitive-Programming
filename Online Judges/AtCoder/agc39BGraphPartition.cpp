#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 200, inf = 1e6; int n;
int edge[maxN][maxN], dist[maxN][maxN];

int floydWarshall()
{
  for (int k = 0; k < n; k ++)
    for (int u = 0; u < n; u ++)
      for (int v = 0; v < n; v ++)
      {
        if (edge[u][v] != 0 && dist[k][u] + dist[k][v] < inf && dist[k][u] == dist[k][v])
          return -1;
        dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
      }
  int ans = 0;
  for (int i = 0; i < n; i ++)
    ans = max(ans, *max_element(dist[i], dist[i]+n) + 1);
  return ans;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      scanf("%1d", &edge[i][j]);
      dist[i][j] = edge[i][j] ? 1 : (i != j) *inf;
    }

  int ans = floydWarshall();
  printf("%d\n", ans);

  return 0;
}