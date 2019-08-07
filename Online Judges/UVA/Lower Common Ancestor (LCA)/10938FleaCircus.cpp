#include <bits/stdc++.h>
using namespace std;

const int maxN = 5000, maxLog = ceil(log2(5000)) + 1; int n, logn;
vector<int> tree[maxN];
int level[maxN], ancestor[maxN][14];
void dfs(int u, int prev)
{
  for (int v: tree[u])
  {
    if (v == prev) continue;
    level[v] = level[u] + 1, ancestor[v][0] = u;
    dfs(v, u);
  }
}
void build()
{
  level[0] = ancestor[0][0] = 0; dfs(0, -1);
  for (int i = 1; i <= logn; i ++)
    for (int u = 0; u < n; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);

  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1) u = ancestor[u][i];

  if (u == v) return(u);

  for (int i = logn; i >= 0; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];

  return(ancestor[u][0]);
}

int main()
{
  int u, v;
  while (scanf("%d", &n) && n)
  {
    for (int i = 0; i < n; i ++) tree[i].clear();
    logn = ceil(log2(n));
    for (int i = 0; i < n - 1; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      tree[u].push_back(v); tree[v].push_back(u);
    }
    build();

    int q; scanf("%d", &q);
    while (q --)
    {
      scanf("%d %d", &u, &v); u --, v --;
      if (level[v] > level[u]) swap(u, v);
      int lca = LCA(u, v);
      int d = level[u] + level[v] - 2*level[lca];
      int ans = u;
      for (int i = 0, dd = d >> 1; dd; dd >>= 1, i ++) if (dd & 1) ans = ancestor[ans][i];
      if (d & 1) // The fleas jump forever between i and j.
        printf("The fleas jump forever between %d and %d.\n", min(ans, ancestor[ans][0]) + 1, max(ans, ancestor[ans][0]) + 1);
      else // The fleas meet at i.
        printf("The fleas meet at %d.\n", ans + 1);
    }
  }
}
