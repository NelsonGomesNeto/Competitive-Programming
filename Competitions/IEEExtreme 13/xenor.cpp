#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxLog = 20;
const lli mod = 1e9 + 7;
vector<pair<int, lli>> tree[maxN];
int level[maxN], ancestor[maxN][maxLog], logDP[maxN + 1]; lli weight[maxN][maxLog];
int n, logn;

void dfs(int u = 0, int prv = -1)
{
  for (auto v: tree[u])
  {
    if (v.first == prv) continue;
    level[v.first] = level[u] + 1, ancestor[v.first][0] = u, weight[v.first][0] = v.second;
    dfs(v.first, u);
  }
}

void build()
{
  level[0] = ancestor[0][0] = 0; dfs();
  for (int i = 1; i < logn; i ++)
    for (int u = 0; u < n; u ++)
    {
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
      // If you want to add something about the path, like weight:
      weight[u][i] = max(weight[u][i - 1], weight[ancestor[u][i - 1]][i - 1]);
    }
}

pair<int, lli> LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);

  lli w = 0;
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
    {
      w = max(w, weight[u][i]);
      u = ancestor[u][i];
    }

  if (u == v) return make_pair(u, w);

  for (int i = logDP[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
    {
      w = max({w, weight[u][i], weight[v][i]});
      u = ancestor[u][i], v = ancestor[v][i];
    }
  w = max({w, weight[u][0], weight[v][0]});

  return make_pair(ancestor[u][0], w);
}

int main()
{
  logDP[1] = 0; for (int i = 2; i <= maxN; i ++) logDP[i] = logDP[i >> 1] + 1;
  scanf("%d", &n); logn = ceil(log2(n));
  int u, v; lli w;
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d %lld", &u, &v, &w); u --, v --;
    tree[u].push_back({v, w}), tree[v].push_back({u, w});
  }
  build();

  lli ans = 0;
  for (int i = 0; i < n; i ++)
    for (int j = i + 1; j < n; j ++)
      ans = (ans + LCA(i, j).second) % mod;
  printf("%lld\n", ans);

  return 0;
}