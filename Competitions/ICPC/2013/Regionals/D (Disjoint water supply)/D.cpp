#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e4, inf = 1e9; int n, m;
int parent[maxN], below[maxN];
bool active[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (v < u) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
int setSize(int u)
{
  return(-parent[root(u)]);
}
vector<int> graph[maxN];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF && n)
  {
    memset(parent, -1, sizeof(parent)), memset(below, 0, sizeof(below)), memset(active, false, sizeof(active));
    for (int i = 0; i < n; i ++) graph[i].clear();
    for (int i = 0, u, v; i < m; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      if (u == 0) active[v] = true;
      else graph[v].push_back(u);
    }

    for (int u = 1; u < n; u ++)
      for (int v: graph[u])
        if (!active[u])
          merge(u, v), active[u] = true;
        else if (root(u) != root(v))
          parent[u] = -1;
    for (int u = 1; u < n; u ++) below[root(u)] ++;
    int total = 0;
    for (int u = 1; u < n; u ++)
      if (active[u])
        total += below[u] * (n - 1 - below[u]);
    printf("%d\n", (total >> 1) + n - 1);
  }
  return(0);
}