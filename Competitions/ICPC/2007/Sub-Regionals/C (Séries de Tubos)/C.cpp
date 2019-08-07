#include <bits/stdc++.h>
using namespace std;

const int maxVertices = 1e3;
vector<int> graph[maxVertices];

bool visited[maxVertices]; int low[maxVertices], in[maxVertices], t = 0;
vector<pair<int, int>> bridges;
void dfs(int u, int prev)
{
  visited[u] = true, in[u] = low[u] = ++ t;
  for (auto v: graph[u])
    if (!visited[v])
    {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u]) bridges.push_back({u, v});
    }
    else if (v != prev) low[u] = min(low[u], in[v]);
}

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) && !(!n && !m))
  {
    bridges.clear();
    for (int i = 0; i < n; i ++) graph[i].clear();
    for (int i = 0, u, v; i < m; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      graph[u].push_back(v), graph[v].push_back(u);
    }
    memset(visited, false, sizeof(visited)), t = 0; dfs(0, -1);
    bool visitedAll = true; for (int i = 0; i < n; i ++) if (!visited[i]) visitedAll = false;
    printf("%c\n", bridges.size() || !visitedAll ? 'N': 'S');
  }
  return(0);
}
