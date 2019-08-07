#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n, m, q;
vector<int> graph[maxN];
bool articulation[maxN], visited[maxN]; int low[maxN], in[maxN], t;
vector<pair<int, int>> bridges;
void dfs(int u, int prv = -1)
{
  visited[u] = true;
  in[u] = low[u] = ++ t;
  for (int v: graph[u])
    if (!visited[v])
    {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u]) bridges.push_back({u, v}), articulation[u] = articulation[v] = true;
    }
    else if (v != prv) low[u] = min(low[u], low[v]);
}
void tarjan()
{
  memset(visited, false, sizeof(visited));
  for (int i = 0; i < n; i ++)
    if (!visited[i])
      dfs(i);
  for (int i = 0; i < n; i ++)
    if (graph[i].size() <= 1)
      articulation[i] = false;
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v), graph[v].push_back(u);
  }
  tarjan();

  scanf("%d", &q);
  while (q --)
  {
    int u; scanf("%d", &u); u --;
    if (articulation[u]) printf("Satisfied %d\n", (int) graph[u].size());
    else printf("Not Satisfied\n");
  }

  return(0);
}