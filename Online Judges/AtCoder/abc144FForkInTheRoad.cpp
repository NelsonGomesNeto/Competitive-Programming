#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 601; int n, m;
vector<int> graph[maxN];

ldouble memo[maxN];
ldouble solve(int blocked)
{
  memo[n] = 0;
  for (int u = n - 1; u >= 1; u --)
  {
    ldouble sum = 0, maximum = 0;
    for (int v: graph[u])
      sum += memo[v], maximum = max(maximum, memo[v]);
    if (u == blocked && graph[u].size() >= 2)
      sum -= maximum;
    memo[u] = 1 + sum / (graph[u].size() - (u == blocked));
  }
  return memo[1];
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v; scanf("%d %d", &u, &v);
    graph[u].push_back(v);
  }

  ldouble ans = 1e18;
  for (int blocked = 0; blocked < n; blocked ++)
    ans = min(ans, solve(blocked));
  printf("%.7Lf\n", ans);

  return 0;
}