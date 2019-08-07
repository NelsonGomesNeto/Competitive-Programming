#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxLog = ceil(log2(1e5)), inf = 1<<20; int n, logn, m;
vector<int> tree[maxN]; set<pair<int, int>> redin, redout;
int level[maxN], ancestor[maxN][maxLog], in[maxN], out[maxN], t;
void dfs(int u, int prev)
{
  in[u] = t ++;
  for (int v: tree[u])
    if (v != prev)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      dfs(v, u);
    }
  out[u] = t ++;
}
void build()
{
  level[0] = ancestor[0][0] = 0; dfs(0, -1);
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
int distance(int u, int v)
{
  return(level[u] + level[v] - 2*level[LCA(u, v)]);
}

int queryWithIterator(set<pair<int, int>> &s, set<pair<int, int>>::iterator it, int u)
{
  int dist = inf;
  for (int i = 0; i < 50; i ++) dist = min(dist, min(distance(u, prev(it, i)->second), distance(u, next(it, i)->second)));
  return(dist);
}
int query(int u)
{
  set<pair<int, int>>::iterator itin = redin.lower_bound({in[u], u}), itout = redout.lower_bound({out[u], u});
  int dist = inf;

  // if (itin != next(redin.begin(), 1)) dist = min(dist, distance(u, prev(itin, 2)->second));
  // if (itin != redin.begin()) dist = min(dist, distance(u, prev(itin, 1)->second));
  // dist = min(dist, distance(u, itin->second));
  // if (itin != prev(redin.end(), 1)) dist = min(dist, distance(u, next(itin, 1)->second));
  // if (itin != prev(redin.end(), 2)) dist = min(dist, distance(u, next(itin, 2)->second));

  return(min(queryWithIterator(redin, itin, u), queryWithIterator(redout, itout, u)));
}

int main()
{
  scanf("%d %d", &n, &m); logn = ceil(log2(n));
  for (int i = 0; i < n - 1; i ++)
  {
    int u, v; scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v); tree[v].push_back(u);
  }
  build();
  redin.insert({in[0], 0}); redout.insert({out[0], 0});

  while (m --)
  {
    int op, u; scanf("%d %d", &op, &u); u --;
    if (op == 1) // paint red
      redin.insert({in[u], u}), redout.insert({out[u], u});
    else
      printf("%d\n", query(u));
  }
  return(0);
}
