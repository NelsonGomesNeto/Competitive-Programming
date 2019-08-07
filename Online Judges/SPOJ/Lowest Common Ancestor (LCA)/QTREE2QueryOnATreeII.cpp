#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e4, maxLog = ceil(log2(1e4)); int n, logn;
vector<pair<int, int>> tree[maxN];
int level[maxN], ancestor[maxN][maxLog]; lli dist[maxN];
void dfs(int u, int prev)
{
  for (auto v: tree[u])
    if (v.first != prev)
    {
      level[v.first] = level[u] + 1, ancestor[v.first][0] = u, dist[v.first] = dist[u] + v.second;
      dfs(v.first, u);
    }
}
void build()
{
  level[0] = ancestor[0][0] = dist[0] = 0; dfs(0, -1);
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1) u = ancestor[u][i];
  if (u == v) return(u);
  for (int i = logn - 1; i >= 0; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return(ancestor[u][0]);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n); logn = ceil(log2(n));
    for (int i = 0; i < n; i ++) tree[i].clear();
    for (int i = 0; i < n - 1; i ++)
    {
      int u, v, c; scanf("%d %d %d", &u, &v, &c); u --, v --;
      tree[u].push_back({v, c}); tree[v].push_back({u, c});
    }
    build();

    char op[5]; int u, v, k;
    while (scanf("%s", op) && strcmp(op, "DONE"))
    {
      scanf("%d %d", &u, &v); u --, v --;
      int lca = LCA(u, v);
      if (!strcmp(op, "DIST")) printf("%lld\n", dist[u] + dist[v] - 2*dist[lca]);
      else
      {
        scanf("%d", &k); k --; int ans = u, diff = k;
        if (k > level[u] - level[lca]) ans = v, diff = (level[v] - level[lca]) - (k - (level[u] - level[lca]));
        for (int i = 0; diff; diff >>= 1, i ++)
          if (diff & 1) ans = ancestor[ans][i];
        printf("%d\n", ans + 1);
      }
    }
  }
  return(0);
}
