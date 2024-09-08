#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
lli a[maxN];
vector<int> graph[maxN];

lli memo[maxN][2];
const lli inf = 1e18;
lli solve(int u = 0, bool hasGold = false)
{
  lli &ans = memo[u][hasGold];
  if (ans != -1) return ans;
  
  if (!hasGold)
  {
    ans = -a[u];
    lli res = -inf;
    for (int v: graph[u])
      res = max(res, solve(v, true));
    ans += res;
  }
  else
  {
    ans = a[u];
    for (int v: graph[u])
      ans = max(ans, solve(v, true));
  }
  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
    {
      graph[i].clear();
      scanf("%lld", &a[i]);
    }

    for (int i = 0; i < m; i++)
    {
      lli u, v; scanf("%lld %lld", &u, &v); u--, v--;
      graph[u].push_back(v);
    }

    memset(memo, -1, sizeof(memo));
    lli ans = -inf;
    for (int u = 0; u < n; u++)
      ans = max(ans, solve(u));
    printf("%lld\n", ans);
  }
  return 0;
}