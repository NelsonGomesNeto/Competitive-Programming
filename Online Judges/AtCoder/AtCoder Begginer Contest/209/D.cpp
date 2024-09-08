#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxLog = 20; int n, q;
int level[maxN], ancestor[maxN][maxLog], logDP[maxN + 1], logn;
vector<int> tree[maxN];

void dfs(int u, int prv = -1)
{
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      dfs(v, u);
    }
}

void build()
{
  level[0] = ancestor[0][0] = 0; dfs(0);
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
    {
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
      // If you want to add something about the path, like weight:
      // weight[u][i] = combination of weight[u][i - 1] and weight[ancestor[u][i - 1]][i - 1]
    }
}

int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);

  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1) u = ancestor[u][i];

  if (u == v) return(u);

  // (i = logn - 1; i >= 0; i --) works as well
  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];

  return(ancestor[u][0]);
}

int main()
{
  logDP[1] = 0; for (int i = 2; i <= maxN; i ++) logDP[i] = logDP[i >> 1] + 1;
  int hehe = 0;
  while (~scanf("%d %d", &n, &q))
  {
    if (hehe++) printf("--------\n");
    logn = ceil(log2(n));
    for (int i = 0; i < n; i++) tree[i].clear();

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }
    build();

    for (int qq = 1; qq <= q; qq++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      int lca = LCA(u, v);

      int distance = level[u] + level[v] - 2*level[lca];
      if (distance & 1) printf("Road\n");
      else printf("Town\n");
    }
  }
  return 0;
}