#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
lli a[maxN];

lli memo[maxN][2][2];
lli solve(int i = 0, bool oneFed = false, bool currFed = false)
{
  if (i >= n) return 0;
  lli &ans = memo[i][oneFed][currFed];
  if (ans != -1) return ans;

  ans = 1e16;
  if (i == 0)
  {
    ans = min(ans, solve(i + 1, true, true) + a[i]);
    ans = min(ans, solve(i + 1, false, false));
  }
  else if (i == n - 1)
  {
    ans = min(ans, solve(i + 1, true, true) + a[i]);
    if (oneFed && currFed)
      ans = min(ans, solve(i + 1, oneFed, false));
  }
  else
  {
    ans = min(ans, solve(i + 1, oneFed, true) + a[i]);
    if (currFed)
      ans = min(ans, solve(i + 1, oneFed, false));
  }

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
