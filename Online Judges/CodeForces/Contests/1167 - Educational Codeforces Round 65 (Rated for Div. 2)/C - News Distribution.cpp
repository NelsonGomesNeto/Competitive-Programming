#include <bits/stdc++.h>
using namespace std;

const int maxN = 5e5; int n, m;
int parent[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &m);

  for (int i = 0; i < m; i ++)
  {
    int k; scanf("%d", &k);
    int u, v;
    if (k) scanf("%d", &u); u --;
    for (int j = 1; j < k; j ++)
    {
      scanf("%d", &v); v --;
      merge(u, v);
    }
  }
  for (int i = 0; i < n; i ++) printf("%d ", setSize(i));
  printf("\n");

  return(0);
}