#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];

lli memo[maxN][2];
lli solve(int i = 0, bool used = false)
{
  if (i >= n - 1) return 0;
  lli &ans = memo[i][used];
  if (ans != -1) return ans;

  ans = solve(i + 1, used) + abs(a[i] - a[i + 1]);
  if (!used)
    ans = min(ans, solve(i + 2, true) + (i + 2 < n ? abs(a[i] - a[i + 2]) : 0));
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    reverse(a, a+n);

    memset(memo, -1, sizeof(memo));
    lli ans = min(solve(), solve(1, true));
    printf("%lld\n", ans);
  }
  return 0;
}