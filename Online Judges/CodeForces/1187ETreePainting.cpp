#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
const int maxN = 2e5; int n;
vector<int> tree[maxN];
int siz[maxN]; lli dp[maxN], ans = 0;
 
int findSize(int u = 0, int prv = -1)
{
  siz[u] = 1;
  for (int v: tree[u])
    if (v != prv)
      siz[u] += findSize(v, u);
  return(siz[u]);
}
lli findDP(int u = 0, int prv = -1)
{
  dp[u] = siz[u];
  for (int v: tree[u])
    if (v != prv)
      dp[u] += findDP(v, u);
  return(dp[u]);
}
void swapRoot(int u, int v)
{
  siz[u] -= siz[v];
  dp[u] -= siz[v] + dp[v];
  siz[v] += siz[u];
  dp[v] += siz[u] + dp[u];
}
void dfs(int u = 0, int prv = -1)
{
  ans = max(ans, dp[u]);
  for (int v: tree[u])
    if (v != prv)
    {
      swapRoot(u, v);
      dfs(v, u);
      swapRoot(v, u);
    }
}
 
int main()
{
  scanf("%d", &n);
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }
  findSize();
  findDP();
 
  dfs();
 
  printf("%lld\n", ans);

  return(0);
}