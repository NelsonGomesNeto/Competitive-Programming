#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e3, inf = 1e8;
int n;
struct Juice { int cost, vitamins; };
Juice juices[maxN];
int dp[maxN][8];

int solve(int i, int vitaminsMask)
{
  if (vitaminsMask == 7) return(0);
  if (i == n) return(inf);
  if (dp[i][vitaminsMask] == -1)
  {
    int ans = solve(i + 1, vitaminsMask);
    ans = min(ans, solve(i + 1, vitaminsMask | juices[i].vitamins) + juices[i].cost);
    dp[i][vitaminsMask] = ans;
  }
  return(dp[i][vitaminsMask]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    int c; char vit[4]; scanf("%d %s", &c, vit);
    juices[i].cost = c, juices[i].vitamins = 0;
    for (int j = 0; vit[j]; j ++) juices[i].vitamins |= 1 << (vit[j] - 'A');
  }

  int ans = solve(0, 0);
  printf("%d\n", ans == inf ? -1 : ans);
  return(0);
}