#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 3e3;
lli s[maxN], ss[maxN], c[maxN], inf = 1e18; int n;
lli dp[maxN][maxN + 2][3];

lli solve(int i, lli prev, int got)
{
  if (got == 3) return(0);
  if (i == n) return(inf);

  if (dp[i][prev + 1][got] == -1)
  {
    lli ans = solve(i + 1, prev, got);
    if (s[i] > prev) ans = min(ans, solve(i + 1, s[i], got + 1) + c[i]);
    dp[i][prev + 1][got] = ans;
  }
  return(dp[i][prev + 1][got]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) { scanf("%lld", &s[i]); ss[i] = s[i]; }
  sort(ss, ss+n);
  for (int i = 0; i < n; i ++) s[i] = lower_bound(ss, ss+n, s[i]) - ss;
  for (int i = 0; i < n; i ++) scanf("%lld", &c[i]);
  lli ans = solve(0, -1, 0);
  printf("%lld\n", ans >= inf ? -1 : ans);
  return(0);
}