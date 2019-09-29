#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 500; int n;
const lli inf = LLONG_MAX;
lli edges[maxN][maxN], dist[maxN][maxN];
int toRemove[maxN];
list<int> vertices;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    vertices.clear();
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        scanf("%lld", &edges[i][j]);
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &toRemove[i]);
      toRemove[i] --;
    }

    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        dist[i][j] = i == j ? 0 : inf;

    lli ans[n];
    for (int i = n - 1; i >= 0; i --)
    {
      int k = toRemove[i];
      vertices.push_back(k);
      for (int u = 0; u < n; u ++)
        dist[k][u] = min(dist[k][u], edges[k][u]),
        dist[u][k] = min(dist[u][k], edges[u][k]);

      for (int u = 0; u < n; u ++)
        for (int v = 0; v < n; v ++)
          if (dist[u][k] != inf && dist[k][v] != inf && dist[u][k] + dist[k][v] < dist[u][v])
            dist[u][v] = dist[u][k] + dist[k][v];

      ans[i] = 0;
      for (int u: vertices)
        for (int v: vertices)
          if (dist[u][v] != inf)
            ans[i] += dist[u][v];
    }

    for (int i = 0; i < n; i ++)
      printf("%lld%c", ans[i], i < n - 1 ? ' ' : '\n');
  }

  return 0;
}