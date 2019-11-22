#include <bits/stdc++.h>
using namespace std;

const int maxN = 8, inf = 1e9; int n, m, l;
int graph[maxN][maxN];
vector<pair<int, pair<int, int>>> edges;
int countryShirts[maxN];

int parent[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(graph, -1, sizeof(graph));
    scanf("%d %d %d", &n, &m, &l);
  
    for (int i = 0; i < n; i ++)
      scanf("%d", &countryShirts[i]);

    for (int i = 0; i < m; i ++)
    {
      int u, v, c; scanf("%d %d %d", &u, &v, &c);
      graph[u][v] = graph[v][u] = c;
    }

    int ans = inf;
    for (int i = 0, end = 1 << (n - 1); i < end; i ++)
    {
      int bitmask = (i << 1) | 1, shirts = 0;
      for (int j = 0; j < n; j ++)
        if (bitmask & (1 << j))
          shirts += countryShirts[j];
      if (shirts < l) continue;

      edges.clear();
      for (int j = 0; j < n; j ++)
        for (int k = j + 1; k < n; k ++)
          if ((bitmask & (1 << j)) && (bitmask & (1 << k)) && graph[j][k] != -1)
            edges.push_back({graph[j][k], {j, k}});
      sort(edges.begin(), edges.end());
      memset(parent, -1, sizeof(parent));

      int minCost = 0;
      for (auto &e: edges)
        if (root(e.second.first) != root(e.second.second))
          merge(e.second.first, e.second.second), minCost += e.first;
      for (int j = 0, r = 0; j < n; j ++)
      {
        if (bitmask & (1 << j) && parent[j] < 0)
          r ++;
        if (r > 1)
          minCost = inf;
      }
      ans = min(ans, minCost);
    }
    printf("%d\n", ans);
  }
  return 0;
}