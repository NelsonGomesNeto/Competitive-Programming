#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const lli mod = 1e9 + 7;
const int maxN = 2e3;
int n, m, k;

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

lli modPow(lli x, lli y)
{
  if (y == 0) return(1);
  lli ret = modPow(x, y >> 1);
  ret = (ret * ret) % mod; if (y & 1) ret = (ret * x) % mod;
  return(ret);
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d %d", &n, &m, &k);
  if (k > n) printf("%lld\n", modPow(m, n));
  else
  {
    for (int i = 0; i <= n - k; i ++)
      for (int u = i, v = i + k - 1; u < v; u ++, v --)
        merge(u, v);
    lli ans = 1;
    for (int i = 0; i < n; i ++) if (parent[i] < 0) ans = (ans * m) % mod;
    printf("%lld\n", ans);
  }
  return(0);
}