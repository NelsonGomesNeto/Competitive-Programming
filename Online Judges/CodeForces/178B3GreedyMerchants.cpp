#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxLog = ceil(log2(1e5)); int n, m, logn;
vector<int> graph[maxN];
int level[maxN], ancestor[maxN][maxLog], in[maxN], low[maxN], bridge[maxN][maxLog], t;
void dfs(int u, int prev)
{
  in[u] = low[u] = ++ t;
  for (int v: graph[u])
    if (in[v] == -1)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u]) bridge[v][0] = 1;
    }
    else if (v != prev) low[u] = min(low[u], in[v]);
}
void build()
{
  level[0] = ancestor[0][0] = t = 0, memset(in, -1, sizeof(in));
  dfs(0, -1);
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
    {
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
      bridge[u][i] = bridge[u][i - 1] + bridge[ancestor[u][i - 1]][i - 1];
    }
}
pair<int, int> LCA(int u, int v)
{
  int b = 0;
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
    {
      b += bridge[u][i];
      u = ancestor[u][i];
    }
  if (u == v) return(make_pair(u, b));
  for (int i = logn - 1; i >= 0; i --)
    if (ancestor[u][i] != ancestor[v][i])
    {
      b += bridge[u][i] + bridge[v][i];
      u = ancestor[u][i], v = ancestor[v][i];
    }
  return(make_pair(ancestor[u][0], b + bridge[u][0] + bridge[v][0]));
}

int main()
{
  scanf("%d %d", &n, &m); logn = ceil(log2(n));
  int u, v;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v); graph[v].push_back(u);
  }
  build();

  int q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d %d", &u, &v); u --, v --;
    pair<int, int> ans = LCA(u, v);
    printf("%d\n", ans.second);
  }
  return(0);
}
