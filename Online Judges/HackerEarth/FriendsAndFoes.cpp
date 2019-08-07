#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, m1, m2;
set<int> enemies[maxN];

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
  if (parent[v] < parent[u]) swap(parent[u], parent[u]);
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
  int n; scanf("%d", &n);
  scanf("%d", &m1);
  for (int i = 0, u, v; i < m1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    merge(u, v);
  }
  scanf("%d", &m2);
  for (int i = 0, u, v; i < m2; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    enemies[u].insert(v), enemies[v].insert(u);
  }

  set<int> groups[n];
  for (int i = 0; i < n; i ++)
    groups[root(i)].insert(i);

  int ans = 0;
  for (int i = 0; i < n; i ++)
    if (groups[i].size())
    {
      bool can = true;
      for (int j: groups[i])
      {
        for (int e: enemies[j])
          if (groups[i].count(e))
          {
            can = false;
            break;
          }
        if (!can) break;
      }
      // printf("%d %d\n", can, (int) groups[i].size());
      if (can) ans = max(ans, (int) groups[i].size());
    }

  printf("%d\n", ans);

  return(0);
}