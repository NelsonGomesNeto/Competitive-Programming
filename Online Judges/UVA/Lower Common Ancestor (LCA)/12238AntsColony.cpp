#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, maxLog = ceil(log2(1e5)) + 1; int n, logn;
vector<pair<int, lli>> tree[maxN];
int level[maxN], ancestor[maxN][maxLog]; lli dist[maxN];
void dfs(int u, int prev)
{
  for (auto v: tree[u])
  {
    if (v.first == prev) continue;
    level[v.first] = level[u] + 1, ancestor[v.first][0] = u, dist[v.first] = dist[u] + v.second;
    dfs(v.first, u);
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
  while (scanf("%d", &n) && n)
  {
    for (int i = 0; i < n; i ++) tree[i].clear(); logn = ceil(log2(n));
    int u, v; lli c;
    for (int i = 1; i < n; i ++)
    {
      scanf("%d %lld", &u, &c);
      tree[i].push_back({u, c}); tree[u].push_back({i, c});
    }
    build();

    int q; scanf("%d", &q);
    for (int i = 0; i < q; i ++)
    {
      if (i) printf(" ");
      scanf("%d %d", &u, &v);
      int lca = LCA(u, v);
      lli d = dist[u] + dist[v] - 2*dist[lca];
      printf("%lld", d);
    } printf("\n");
  }
  return(0);
}
