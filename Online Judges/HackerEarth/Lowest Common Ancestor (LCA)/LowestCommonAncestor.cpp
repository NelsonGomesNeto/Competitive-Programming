#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxLog = floor(log2(maxN)); int n, logn;
vector<int> tree[maxN];
int level[maxN], ancestor[maxN][20];
void dfs(int u)
{
  for (int v: tree[u])
  {
    level[v] = level[u] + 1, ancestor[v][0] = u;
    dfs(v);
  }
}
void build()
{
  level[0] = ancestor[0][0] = 0; dfs(0);
  for (int i = 1; i <= logn; i ++)
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

  for (int i = 0; ancestor[u][i] != ancestor[v][i]; i ++)
    u = ancestor[u][i], v = ancestor[v][i];

  return(ancestor[u][0]);
}

int main()
{
  scanf("%d", &n); logn = floor(log2(n)) + 1;
  for (int i = 1; i < n; i ++)
  {
    int u; scanf("%d", &u);
    tree[u].push_back(i);
  }
  build();

  int q, u, v; scanf("%d", &q);
  scanf("%d", &u); q --;
  while(q --)
  {
    scanf("%d", &v);
    u = LCA(u, v);
  }

  printf("%d\n", u);

  return(0);
}
