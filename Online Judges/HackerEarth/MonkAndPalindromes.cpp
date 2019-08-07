#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial
  Each query means that between A and B: there must be a palindrome
  So, string[A] == string[B], string[A + 1] == string[B - 1], ...
  Use DSU to merge those pair of positions: (A, B), (A + 1, B - 1), ...
  Since these positions *must* have the same digits
  ans = 1
  For every group (from the DSU):
    ans = (ans * 10) % mod
    (since there are 10 possible digits, and if you assign digit x
    to anyone in this group, every other position *must* receive digit x)
*/

const int maxN = 1e3; int n, m;
const lli mod = 1e9 + 7;

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
  return(-1 * parent[u]);
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d\n%d", &n, &m);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    if (u > v) swap(u, v);
    for (int lo = u, hi = v; lo < hi; lo ++, hi --) merge(lo, hi);
  }

  lli ans = 1;
  for (int i = 0; i < n; i ++)
    if (parent[i] < 0)
      ans = (ans * 10LL) % mod;

  printf("%lld\n", ans);

  return(0);
}