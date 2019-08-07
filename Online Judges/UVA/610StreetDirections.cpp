#include <bits/stdc++.h>
using namespace std;

const int maxV = 1000; int n, m;
vector<int> graph[maxV];
vector<pair<int, int>> edges;
int in[maxV], low[maxV], t;
void dfs(int u, int prev)
{
  in[u] = low[u] = ++ t;
  for (int v: graph[u])
    if (in[v] == -1)
    {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      edges.push_back({u, v}); // Add tree's street
      if (low[v] > in[u]) edges.push_back({v, u});
      // If it's a bridge, the only way to go back is through this same edge
    }
    else if (v != prev && in[u] > in[v]) low[u] = min(low[u], in[v]), edges.push_back({u, v});
    // If I can go back to a node that higher, we must have a street to there
    // Otherwise, I would add another edge to an street that we already have a path to
}
void findBridges()
{
  memset(color, 0, sizeof(color));
  t = 0; memset(in, -1, sizeof(in)); edges.clear();
  for (int i = 0; i < n; i ++)
    if (in[i] == -1)
      dfs(i, -1);
}

int main()
{
  int r = 0;
  while (scanf("%d %d", &n, &m) && !(!n && !m))
  {
    for (int i = 0; i < n; i ++) graph[i].clear();
    for (int i = 0; i < m; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      graph[u].push_back(v); graph[v].push_back(u);
    }
    findBridges();
    sort(edges.begin(), edges.end());

    printf("%d\n\n", ++ r);
    for (auto e: edges) printf("%d %d\n", e.first + 1, e.second + 1);
    printf("#\n");
  }
  return(0);
}
