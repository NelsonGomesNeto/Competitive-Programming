#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 3e5; int n;
const lli inf = LLONG_MAX;
lli a[maxN + 3], b[maxN + 3];

lli memo[maxN + 3][3];
lli solve(int i = 1, lli prvK = 0)
{
  if (i == n + 1) return 0;
  if (memo[i][prvK] == -1)
  {
    lli ans = inf;
    for (lli k = 0; k <= 2; k ++)
      if (a[i] + k != a[i - 1] + prvK)
        ans = min(ans, solve(i + 1, k) + k*b[i]);
    memo[i][prvK] = ans;
  }
  return memo[i][prvK];
}

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d", &n);
    a[0] = a[n + 1] = -3, b[0] = b[n + 1] = 1e9;
    for (int i = 1; i <= n; i ++)
      scanf("%lld %lld", &a[i], &b[i]);

    for (int i = 0; i <= n; i ++)
      for (int j = 0; j <= 2; j ++)
        memo[i][j] = -1;
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return(0);
}
