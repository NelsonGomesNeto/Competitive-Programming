#include <bits/stdc++.h>
using namespace std;
#define lli long long int

const int maxN = 1e5; int n;
vector<int> tree[maxN]; lli a[maxN];

lli memo[maxN];
lli dfs(int u, int prev, lli s)
{
  lli sum = s;
  for (int v: tree[u])
    if (v != prev)
    {
      sum += dfs(v, u, s ^ a[v]);
      sum += dfs(v, u, a[v]);
    }
  return(sum);
}

int main()
{
  scanf("%d", &n); for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }
  lli ans = dfs(0, -1, a[0]);
  for (int i = 0; i < n; i ++) ans += a[i];
  printf("%lld\n", ans);
  return(0);
}