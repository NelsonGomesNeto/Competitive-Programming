#include <bits/stdc++.h>
using namespace std;
#define MAXLEVELS (int) 1e5 + 1
int n, m, inf = 1<<30;
int e[MAXLEVELS];
unordered_map<int, int> dp[MAXLEVELS];
// force, cost
vector<pair<int, int> > stores[MAXLEVELS];

int solve(int energy, int level)
{
  if (level == n + 1) return(0);

  if (!dp[level].count(energy))
  {
    int ans = energy < e[level] ? inf : solve(energy - e[level], level + 1);
    for (auto store: stores[level])
      ans = min(ans, solve(store.first - e[level], level + 1) + store.second);
    dp[level][energy] = ans;
  }

  return(dp[level][energy]);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i ++) scanf("%d", &e[i]);
  for (int i = 0; i < m; i ++)
  {
    int l, s, c; scanf("%d %d %d", &l, &s, &c);
    if (s >= e[l]) stores[l].push_back({s, c});
  }

  int minCost = solve(0, 1);
  printf("%d\n", minCost == inf ? -1 : minCost);
  return(0);
}
