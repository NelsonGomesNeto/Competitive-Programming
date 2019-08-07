#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  Let's split the graph into components, more then that, into components with edges 0
  and components with edges 1. That can be done easily using DSU.
  ans = 0
  Now for every root i from "edges 0", ans += setSize(i, 0) * (setSize(i) - 1, 0)
  Now for every root i from "edges 1", ans += setSize(i, 1) * (setSize(i) - 1, 1)
    Since for each vertex, you can reach n - 1 vertices, and there are n vertices.
  There are some vertices that belongs to both "edges 0" and "edges 1". So, for each
  one of them: ans += (setSize(i, 0) - 1) * (setSize(i, 1) - 1)
    Since for each vertex, you can reach n - 1 vertices, but there are n - 1 vertices
    (Otherwise, you would be adding a pair from "edges 0" or "edges 1")
*/

const int maxN = 2e5; int n;

int parent[2][maxN];
int root(int u, int c)
{
  if (parent[c][u] < 0) return(u);
  return(parent[c][u] = root(parent[c][u], c));
}
void merge(int u, int v, int c)
{
  u = root(u, c), v = root(v, c);
  if (u == v) return;
  if (parent[c][v] < parent[c][u]) swap(u, v);
  parent[c][u] += parent[c][v];
  parent[c][v] = u;
}
int setSize(int u, int c)
{
  return(-1 * parent[c][root(u, c)]);
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d", &n);
  for (int i = 0, u, v, c; i < n - 1; i ++)
  {
    scanf("%d %d %d", &u, &v, &c); u --, v --;
    merge(u, v, c);
  }

  lli total = 0;
  for (int i = 0; i < n; i ++)
  {
    if (parent[0][i] < 0) total += (lli) setSize(i, 0) * (setSize(i, 0) - 1);
    if (parent[1][i] < 0) total += (lli) setSize(i, 1) * (setSize(i, 1) - 1);
    total += (lli) (setSize(i, 0) - 1) * (setSize(i, 1) - 1);
  }
  printf("%lld\n", total);

  return(0);
}
