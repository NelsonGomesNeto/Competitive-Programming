#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1000, maxM = 10; int n, m;
const lli mod = 1e9 + 7;

lli memo[maxM][maxN + 1], inv2 = 500000004;
lli solve(int i = m - 1, int diff = n)
{
  if (i == 0) return (diff * (diff + 1) % mod) * inv2 % mod;
  if (memo[i][diff] != -1) return memo[i][diff];
  lli ans = 0;
  for (int d = diff; d >= 0; d --)
    ans = (ans + (diff - d + 1) * solve(i - 1, d) % mod) % mod;
  return memo[i][diff] = ans;
}

int main()
{
  memset(memo, -1, sizeof(memo));
  n = maxN, m = maxM;
  solve();

  while (scanf("%d %d", &n, &m) != EOF)
  {
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
