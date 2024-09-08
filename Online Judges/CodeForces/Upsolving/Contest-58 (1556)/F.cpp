#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  count the number of winners


  count the number of arrangements
    simple
*/

const int maxN = 14; int n;
const lli mod = 1e9 + 7;
lli a[maxN];

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

int all;
lli memo[maxN][1 << maxN];
lli solve(int i, int mask)
{
  if (mask == all) return 1;
  lli &ans = memo[i][mask];
  if (ans != -1) return ans;

  ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if ((mask & (1 << i)) && (~mask & (1 << j)))
        ans = (ans + solve(i, mask | (1 << j)) * a[i] % mod * inv(a[i] + a[j]) % mod) % mod;
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    all = (1 << n) - 1;
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    lli ans = 0;
    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; i++)
      ans = (ans + solve(i, 1 << i)) % mod;
    // ans = ans * inv(modPow(2, n * (n + 1) >> 1)) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}
