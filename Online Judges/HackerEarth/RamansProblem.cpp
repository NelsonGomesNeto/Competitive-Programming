#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
const lli mod = 1e9 + 7;
pair<int, pair<int, int>> edges[maxN - 1];

int parent[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
lli setSize(int u)
{
  return(-1 * parent[root(u)]);
}
lli merge(int u, int v)
{
  lli sum = 1;
  u = root(u), v = root(v);
  if (u == v) return(sum);
  sum = (sum * setSize(u) % mod) * setSize(v) % mod;
  if (parent[v] < parent[u]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
  return(sum);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    memset(parent, -1, sizeof(int)*n);
    for (lli i = 0, u, v, c; i < n - 1; i ++)
    {
      scanf("%lld %lld %lld", &u, &v, &c); u --, v --;
      edges[i] = {c, {u, v}};
    }
    sort(edges, edges+n-1);

    lli ans = 0;
    for (int i = 0; i < n - 1; i ++)
    {
      lli sum = merge(edges[i].second.first, edges[i].second.second);
      ans = (ans + sum * edges[i].first % mod) % mod;
    }
    printf("%lld\n", ans);
  }
  return(0);
}