#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 400, maxQ = 1e5, inf = 1e8; int n, r;
pair<int, int> temperatures[2][maxN];
int edges[maxN][maxN];
int dist[2][maxN][maxN];
struct Query { int u, v, id; };
vector<Query> queries[2][maxN];
int ans[maxQ];

int main()
{
  scanf("%d %d", &n, &r);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &temperatures[0][i].first);
    temperatures[0][i].second = i;
    temperatures[1][i] = temperatures[0][i];
    edges[i][i] = 0;
  }
  sort(temperatures[0], temperatures[0]+n);
  sort(temperatures[1], temperatures[1]+n, greater<pair<int, int>>());

  for (int i = 0; i < r; i ++)
  {
    int u, v, d; scanf("%d %d %d", &u, &v, &d); u --, v --;
    edges[u][v] = edges[v][u] = d;
  }

  int q; scanf("%d", &q);
  for (int i = 0; i < q; i ++)
  {
    int u, v, k, t; scanf("%d %d %d %d", &u, &v, &k, &t); u --, v --, k --;
    queries[t][k].push_back({u, v, i});
  }

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      dist[0][i][j] = dist[1][i][j] = i == j ? 0 : edges[i][j] ? edges[i][j] : inf;
  for (int t = 0, kk = 0; t < 2; t ++, kk = 0)
  {
    for (int i = 0; i < n;)
    {
      int j = i;
      while (j < n && temperatures[t][j].first == temperatures[t][i].first)
      {
        int k = temperatures[t][j].second;
        for (int u = 0; u < n; u ++)
          if (edges[k][u])
            dist[t][k][u] = min(dist[t][k][u], edges[k][u]);

        for (int u = 0; u < n; u ++)
          for (int v = 0; v < n; v ++)
            if (dist[t][u][k] + dist[t][k][v] < dist[t][u][v])
              dist[t][u][v] = dist[t][u][k] + dist[t][k][v];
        j ++;
      }
      for (Query &q: queries[t][kk])
        ans[q.id] = dist[t][q.u][q.v];
      i = j, kk ++;
    }
    for (; kk < n; kk ++)
      for (Query &q: queries[t][kk])
        ans[q.id] = dist[t][q.u][q.v];
  }

  for (int i = 0; i < q; i ++)
    printf("%d\n", ans[i] == inf ? -1 : ans[i]);

  return 0;
}