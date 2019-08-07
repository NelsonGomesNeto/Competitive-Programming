#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, k;
int s[maxN];
int biggest = 0;

int parent[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
  biggest = max(biggest, setSize(u));
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i ++) scanf("%1d", &s[i]);
  for (int i = 0; i < n; i ++)
    if (s[i] == 1)
    {
      int lo = i;
      while (i + 1 < n && s[i + 1] == 1) merge(lo, ++ i);
    }
  while (k --)
  {
    int op, i; scanf("%d", &op); if (op == 2) scanf("%d", &i); i --;
    if (op == 1) printf("%d\n", biggest);
    else
    {
      s[i] = 1, biggest = max(biggest, 1);
      if (i && s[i - 1] == 1) merge(i - 1, i);
      if (i < n - 1 && s[i + 1] == 1) merge(i, i + 1);
    }
  }
  return(0);
}