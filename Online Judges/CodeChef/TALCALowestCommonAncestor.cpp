#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5, maxLog = ceil(log2(2e5)) + 1; int n, logn;
vector<int> tree[maxN];
int level[maxN], ancestor[maxN][maxLog], logDP[maxN + 1];
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

  // (i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --) works as well
  for (i = logn; i >= 0; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];

  return(ancestor[u][0]);
}

int main()
{
  logDP[0] = logDP[1] = 0; for (int i = 2; i <= maxN; i ++) logDP[i] = logDP[i >> 1] + 1;
  scanf("%d", &n); logn = ceil(log2(n));
  int u, v;
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v); tree[v].push_back(u);
  }
  build();

  int r, q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d %d %d", &r, &u, &v); r --, u --, v --;
    int lca = LCA(u, v), ru = LCA(r, u), rv = LCA(r, v);
    if (level[ru] > level[lca]) lca = ru;
    if (level[rv] > level[lca]) lca = rv;
    printf("%d\n", lca + 1);
    /* It's kind of easy to see why it works, just think about every possible
    position for the root to be, and look at the lca, ru and rv; the lowest one
    will indeed be the answer
    */
  }
  return(0);
}
