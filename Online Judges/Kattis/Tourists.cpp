#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5, maxLog = ceil(log2(2e5)); int n, logn;
vector<int> tree[maxN];
int level[maxN], ancestor[maxN][maxLog], logDP[maxN + 1];

void dfs(int u = 0, int prv = -1)
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
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
      u = ancestor[u][i];
  if (u == v) return(u);
  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return(ancestor[u][0]);
}

int main()
{
  for (int i = 2; i <= maxN; i ++) logDP[i] = logDP[i >> 1] + 1;
  scanf("%d", &n); logn = ceil(log2(n));
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }
  build();

  lli ans = 0;
  for (int i = 1; i <= n; i ++)
    for (int j = 2; i*j <= n; j ++)
    {
      int lca = LCA(i - 1, i*j - 1);
      lli dist = level[i - 1] + level[i*j - 1] - 2*level[lca] + 1;
      ans += dist;
    }
  printf("%lld\n", ans);

  return(0);
}