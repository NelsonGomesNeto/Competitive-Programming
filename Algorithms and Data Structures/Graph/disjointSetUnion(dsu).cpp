#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e6; int n;
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
  int n, m; scanf("%d %d", &n, &m);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v);
    merge(u, v);
  }

  for (int i = 0; i < n; i ++)
    printf("root(%d) = %d || size: %d\n", i, root(i), setSize(i));

  return(0);
}