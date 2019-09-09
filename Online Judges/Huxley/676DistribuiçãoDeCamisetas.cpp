#include <bits/stdc++.h>
using namespace std;

const int maxN = 8, inf = 1e9; int n, m, l;
vector<pair<int, int>> graph[maxN];
int countryShirts[maxN];

int dist[maxN][maxN], nxt[maxN][maxN], edges[maxN][maxN];
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
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(edges, -1, sizeof(edges));
    scanf("%d %d %d", &n, &m, &l);
  
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &countryShirts[i]);
      graph[i].clear();
    }

    for (int i = 0; i < m; i ++)
    {
      int u, v, c; scanf("%d %d %d", &u, &v, &c);
      graph[u].push_back({v, c}), graph[v].push_back({u, c});
      edges[u][v] = edges[v][u] = c;
    }
    floydWarshall();
    
    vector<int> all;
    for (int i = 0; i < n; i ++)
      all.push_back(i);

    int ans = inf;
    do
    {
      int shirts = l, cost = 0;
      for (int i = 0; i < all.size(); i ++)
      {
        int minCost = dist[0][all[i]];
        for (int j = 0; j < i; j ++)
          minCost = min(minCost, dist[all[j]][all[i]]);
        shirts -= countryShirts[all[i]], cost += minCost;
        if (shirts <= 0) break;
      }
      if (shirts <= 0) ans = min(ans, cost);
    } while (next_permutation(all.begin(), all.end()));
    printf("%d\n", ans);
  }
  return 0;
}