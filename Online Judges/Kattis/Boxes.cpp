#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5, maxLog = ceil(log2(2e5)); int n, logn, now; vector<int> roots;
int childsRoot[maxN], below[maxN];
vector<int> tree[maxN];
int level[maxN], ancestor[maxN][maxLog], logDP[maxN + 1];

int dfs(int u, int prv = -1)
{
  childsRoot[u] = now;
  below[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      below[u] += dfs(v, u);
    }
  return(below[u]);
}
void build()
{
  for (int root: roots)
  {
    level[root] = ancestor[root][0] = 0, now = root;
    dfs(root);
  }
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
  for (int i = 0, p; i < n; i ++)
  {
    scanf("%d", &p);
    if (p == 0) roots.push_back(i);
    else tree[p - 1].push_back(i), tree[i].push_back(p - 1);
  }
  build();

  int q; scanf("%d", &q);
  while (q --)
  {
    int m; scanf("%d", &m);
    set<pair<int, int>> all;
    for (int i = 0, u; i < m; i ++)
    {
      scanf("%d", &u); u --;
      all.insert({level[u], u});
    }
    int ans = 0;
    vector<int> lcas;
    for (auto &i: all)
    {
      bool done = false;
      for (int l: lcas)
        if (childsRoot[i.second] == childsRoot[l] && LCA(i.second, l) == l)
        {
          done = true;
          break;
        }
      if (!done)
        ans += below[i.second], lcas.push_back(i.second);
    }
    printf("%d\n", ans);
  }

  return(0);
}