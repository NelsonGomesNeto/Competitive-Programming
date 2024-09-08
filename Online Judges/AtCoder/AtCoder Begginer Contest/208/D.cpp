#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e2; int n, m;
const lli inf = 1e17;
int edges[maxN][maxN];

lli dist[maxN][maxN]; int nxt[maxN][maxN];
lli floydWarshall()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (i == j) dist[i][j] = 0;
      else if (edges[i][j] != -1) dist[i][j] = edges[i][j], nxt[i][j] = j;
      else dist[i][j] = inf;

  lli ans = 0;
  for (int k = 0; k < n; k++)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j], nxt[i][j] = nxt[i][k];

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (dist[i][j] != inf)
          ans += dist[i][j];
  }
  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    memset(edges, -1, sizeof(edges));
    for (int i = 0; i < m; i++)
    {
      int u, v; lli c; scanf("%d %d %lld", &u, &v, &c); u--, v--;
      edges[u][v] = c;
    }

    lli ans = floydWarshall();
    printf("%lld\n", ans);
  }
  return 0;
}