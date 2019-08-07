#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, q, m;
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
  scanf("%d %d", &n, &q);
  for (int i = 0, u, v; i < q; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    merge(u, v);
  }

  scanf("%d", &m);
  set<int> doneRoots, allRoots;
  for (int i = 0, u; i < m; i ++)
  {
    scanf("%d", &u); u --;
    doneRoots.insert(root(u));
  }
  for (int i = 0; i < n; i ++) if (parent[i] < 0) allRoots.insert(i);
  printf("%d\n", (int) (allRoots.size() - doneRoots.size()));

  return(0);
}