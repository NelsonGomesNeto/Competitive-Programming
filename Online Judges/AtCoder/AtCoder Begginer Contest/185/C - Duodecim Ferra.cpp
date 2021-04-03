#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxSz = 200, maxCuts = 11;
int n;

lli memo[maxSz + 1][maxCuts];
lli solve2(int sz, int cuts = 0)
{
  if (cuts == 11) return 1;
  lli &ans = memo[sz][cuts];
  if (ans != -1) return ans;

  ans = 0;
  for (int i = 1; i < sz; i++)
    ans += solve2(sz - i, cuts + 1);
  return ans;
}
lli solve(int sz = n)
{
  if (sz <= 11) return 0;
  return solve2(sz);
}

int main()
{
  while (~scanf("%d", &n))
  {
    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}