#include <bits/stdc++.h>
using namespace std;

int root(int v, int parent[])
{
  if (parent[v] < 0) return(v);
  parent[v] = root(parent[v], parent);
  return(parent[v]);
}

int isSameSet(int v, int u, int parent[])
{
  return(root(v, parent) == root(u, parent));
}

void merge(int v, int u, int parent[])
{
  v = root(v, parent);
  u = root(u, parent);
  if (v == u) return;

  if (parent[u] < parent[v])
  {
    int aux = parent[u];
    parent[u] = parent[v];
    parent[v] = aux;
  }

  parent[v] += parent[u];
  parent[u] = v;
}

int setSize(int v, int parent[])
{
  return(-parent[root(v, parent)]);
}

int main()
{
  int r = 0;
  while (1)
  {
    r ++;
    int p;
    if (scanf("%d", &p) == EOF) break;
    int n; scanf("%d", &n);
    int parent[p]; for (int i = 0; i < p; i ++) parent[i] = -1;
    int d = p, m = 0;
    for (int i = 0; i < n; i ++)
    {
      int u, v; scanf("%d %d", &u, &v);
      if (!isSameSet(u, v, parent))
      {
        d --;
        merge(u, v, parent);
      }
    }
    for (int i = 0; i < p; i ++) m = max(m, setSize(i, parent));

    printf("caso %d: %d %d\n", r, d, m);
  }
  return(0);
}