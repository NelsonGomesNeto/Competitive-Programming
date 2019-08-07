#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxLog = ceil(log2(1e5)); int n, logn;
vector<int> tree[maxN];
int level[maxN], ancestor[maxN][maxLog], pass[maxN], in[maxN], out[maxN], e[maxN][2];
map<int, int> edges[maxN];
void dfs(int u, int prev)
{
  for (int v: tree[u])
    if (v != prev)
    {
      level[v] = level[u] + 1, ancestor[v][0] = u;
      dfs(v, u);
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

int fill(int u, int prev)
{
  int sum = pass[u]; // -out[u]
  for (int v: tree[u])
    if (v != prev)
    {
      int s = fill(v, u);
      edges[min(u, v)][max(u, v)] += s;
      sum += s;
    }
  return(sum); // sum + in[u]
}

int main()
{
  scanf("%d", &n); logn = ceil(log2(n));
  int u, v;
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --; e[i][0] = min(u, v), e[i][1] = max(u, v);
    edges[min(u, v)][max(u, v)] = 0;
    tree[u].push_back(v); tree[v].push_back(u);
  }
  build();

  int q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d %d", &u, &v); u --, v --;
    int lca = LCA(u, v);
    in[u] ++, in[v] ++, out[lca] += 2;
    pass[u] ++, pass[v] ++, pass[lca] -= 2;
  }
  fill(0, -1);

  for (int i = 0; i < n - 1; i ++)
    printf("%d ", edges[e[i][0]][e[i][1]]);
  printf("\n");

  return(0);
}
