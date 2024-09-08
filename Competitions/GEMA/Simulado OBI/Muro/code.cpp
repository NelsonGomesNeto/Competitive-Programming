#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int n;
const lli mod = 1e9 + 7;

lli memo[maxN + 1];
lli d[4] = {0, 1, 4, 2};
lli solve(int i = 0)
{
  if (i > n) return 0;
  if (i == n) return 1;
  lli &ans = memo[i];
  if (ans != -1) return ans;

  ans = 0;
  for (int j = 1; j <= 3; j++)
    ans = (ans + solve(i + j) * d[j] % mod) % mod;
  return ans;
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