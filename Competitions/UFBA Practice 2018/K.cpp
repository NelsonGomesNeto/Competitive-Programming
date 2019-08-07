#include <bits/stdc++.h>
using namespace std;
#define lli long long int
int a[(int) 5e4], n; lli acc[(int) 5e4 + 553];
lli dp[184][(int) 5e4 + 1];
// 184 is from: 3(sum (i = 1 to n) (i)) == 5e4; which gives us: n^2 + n - 5e4*2/3 = 0
// 553 is from: n + 3*184; which is the limit it can reach jumping, and not even that hahaha

lli solve(int turn, int i)
{
  if (i >= n) return(0);
  if (dp[turn][i] == -1)
  {
    dp[turn][i] = solve(turn + 1, i + 3*turn);
    dp[turn][i] = max(dp[turn][i], solve(turn + 1, i + 3*turn) + acc[i + 3*turn] - acc[i]);
  }
  return(dp[turn][i]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  acc[0] = 0; for (int i = 0; i < n; i ++) acc[i + 1] = acc[i] + a[i];
  for (int i = n + 1; i < n + 553; i ++) acc[i] = acc[i - 1];

  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < n; i ++)
  {
    solve(1, i);
    printf("%lld\n", dp[1][i]);
  }
  return(0);
}
