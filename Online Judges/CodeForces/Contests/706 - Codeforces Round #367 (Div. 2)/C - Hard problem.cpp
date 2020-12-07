#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli dp[(int) 1e5][2], cost[(int) 1e5], inf = 1e18;
string normal[(int) 1e5], reversed[(int) 1e5];

lli topdown(int i, int s, int done)
{
  if (i == s) return(0);
  if (dp[i][done] == -1)
  {
    lli ans = inf;
    if (normal[i - 1] <= normal[i])
      ans = min(topdown(i + 1, s, 0), ans);
    if (reversed[i - 1] <= normal[i])
      ans = min(topdown(i + 1, s, 0) + (1 - done) * cost[i - 1], ans);
    if (normal[i - 1] <= reversed[i])
      ans = min(topdown(i + 1, s, 1) + cost[i], ans);
    if (reversed[i - 1] <= reversed[i])
      ans = min(topdown(i + 1, s, 1) + (1 - done) * cost[i - 1] + cost[i], ans);
    dp[i][done] = ans;
  }
  return(dp[i][done]);
}

lli bottomup(int s)
{
  dp[0][0] = 0; dp[0][1] = cost[0];
  for (int i = 1; i < s; i ++)
  {
    dp[i][0] = dp[i][1] = inf;
    if (normal[i - 1] <= normal[i])
      dp[i][0] = min(dp[i][0], dp[i - 1][0]);
    if (reversed[i - 1] <= normal[i])
      dp[i][0] = min(dp[i][0], dp[i - 1][1]);
    if (normal[i - 1] <= reversed[i])
      dp[i][1] = min(dp[i][1], dp[i - 1][0] + cost[i]);
    if (reversed[i - 1] <= reversed[i])
      dp[i][1] = min(dp[i][1], dp[i - 1][1] + cost[i]);
  }
  return(min(dp[s - 1][0], dp[s - 1][1]));
}

int main()
{
  int s; scanf("%d", &s);
  for (int i = 0; i < s; i ++)
    scanf("%lld", &cost[i]);
  for (int i = 0; i < s; i ++)
  {
    getchar();
    cin >> normal[i];
    reversed[i] = normal[i];
    reverse(reversed[i].begin(), reversed[i].end());
  }

  //lli best = topdown(1, s, 0);
  lli best = bottomup(s);

  printf("%lld\n", best >= inf ? -1 : best);

  return(0);
}