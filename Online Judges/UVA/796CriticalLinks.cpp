#include <bits/stdc++.h>
using namespace std;

const int maxV = 1e6; int n;
vector<int> graph[maxV];
vector<pair<int, int>> bridges;
int in[maxV], low[maxV], t;
void dfs(int u, int prev)
{
  in[u] = low[u] = ++ t;
  for (int v: graph[u])
    if (in[v] == -1) // not visited
    {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u]) bridges.push_back({min(u, v), max(u, v)});
    }
    else if (v != prev) low[u] = min(low[u], in[v]); // I can reach him
}
void findBridges()
{
  t = 0; memset(in, -1, sizeof(in)); bridges.clear();
  for (int i = 0; i < n; i ++)
    if (in[i] == -1)
      dfs(i, -1);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++) graph[i].clear();
    for (int i = 0; i < n; i ++)
    {
      int u, v, m; scanf("%d (%d) ", &u, &m);
      while (m --)
      {
        scanf("%d", &v);
        graph[u].push_back(v);
      }
    }
    findBridges();
    sort(bridges.begin(), bridges.end());

    printf("%d critical links\n", (int) bridges.size());
    for (auto i: bridges) printf("%d - %d\n", i.first, i.second);
    printf("\n");
  }
  return(0);
}
