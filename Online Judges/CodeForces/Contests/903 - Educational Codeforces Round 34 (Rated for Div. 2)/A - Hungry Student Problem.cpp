#include <bits/stdc++.h>
using namespace std;

int dp[101];

void solve(int x)
{
  if (x > 100) return;
  solve(x + 3); solve(x + 7);
  dp[x] = 1;
}

int main()
{
  memset(dp, 0, sizeof(dp));
  solve(0);
  int tests; scanf("%d", &tests);
  while (tests -- > 0)
  {
    int x; scanf("%d", &x);
    if (dp[x])
      printf("YES\n");
    else
      printf("NO\n");
  }
  return(0);
}