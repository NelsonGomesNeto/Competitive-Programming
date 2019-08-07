#include <bits/stdc++.h>
using namespace std;

/* Explanation:
First in the DFS, we count how many nodes a node can reach (downwards)
The query will have 4 cases:
  1 (u == v): the whole tree
  2 (distance is odd): there won't be a single edge in the middle
  3 (level[u] == level[v]): they will meet at their lca
    ans = whole tree - nodes[node below lca for u] - nodes[node below lca for v]
  4 (level[u] != level[v]): they will meet below their lca
    make u be the lowest of them
    ans = nodes[meeting node] - nodes[node below meeting for u]
*/

const int maxN = 1e5, maxLog = ceil(log2(1e5)); int n, logn;
vector<int> tree[maxN];
int level[maxN], ancestor[maxN][maxLog], nodes[maxN];
void dfs(int u, int prev)
{
  nodes[u] = 1;
  for (int v: tree[u])
    if (v != prev)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      dfs(v, u);
      nodes[u] += nodes[v];
    }
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

int main()
{
  scanf("%d", &n); logn = ceil(log2(n));
  int u, v;
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
    int lca = LCA(u, v);
    int d = level[u] + level[v] - 2*level[lca];
    if (u == v) printf("%d\n", nodes[0]);
    else if (d & 1) printf("0\n");
    else if (level[v] == level[u])
    {
      for (int diff = level[u] - level[lca] - 1, i = 0; diff; diff >>= 1, i ++)
        if (diff & 1) u = ancestor[u][i], v = ancestor[v][i];
      printf("%d\n", nodes[0] - nodes[u] - nodes[v]);
    }
    else
    {
      if (level[v] > level[u]) swap(u, v);
      int mid = u;
      for (int diff = (d >> 1) - 1, i = 0; diff; diff >>= 1, i ++)
        if (diff & 1) mid = ancestor[mid][i];
      printf("%d\n", nodes[ancestor[mid][0]] - nodes[mid]);
    }
  }

  return(0);
}
