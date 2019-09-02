#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
const lli inf = 1e16;
lli a[maxN];

lli memo[maxN][3];
lli solve(int i = 0, int current = 1)
{
  if (i == n) return(0);
  if (memo[i][current+1] == -1)
  {
    lli ans = inf;
    if (!(i + 1 == n && current == -1))
      ans = min(ans, solve(i + 1, current) + abs(1LL - a[i]));
    if (!(i + 1 == n && current == 1))
      ans = min(ans, solve(i + 1, current*-1) + abs(-1LL - a[i]));
    memo[i][current+1] = ans;
  }
  return(memo[i][current+1]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%lld", &a[i]);

  memset(memo, -1, sizeof(memo));
  lli ans = solve();
  printf("%lld\n", ans);

  return(0);
}
