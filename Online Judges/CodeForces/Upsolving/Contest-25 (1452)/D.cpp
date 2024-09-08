#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 5; int n;
const lli mod = 998244353;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

lli memo[maxN], suffix[maxN];
lli solve(int i);
lli suff(int i)
{
  if (i > n) return i == n + 1;
  lli &ans = suffix[i];
  if (ans != -1) return ans;
  return ans = (suff(i + 2) + solve(i)) % mod;
}
lli solve(int i = 1)
{
  if (i > n) return i == n + 1;
  lli &ans = memo[i];
  if (ans != -1) return ans;

  int end = (n + 1 - i) & 1 ? n + 1 - i : n + 1 - i + 1;
  ans = (suff(i + 1) - suff(i + end + 1) + mod) % mod;
  // ans = 0;
  // for (int j = 1; j <= end; j += 2)
  //   ans = (ans + solve(i + j)) % mod;
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(memo, -1, sizeof(memo));
    memset(suffix, -1, sizeof(suffix));
    lli ways = solve();
    lli ans = ways * inv(modPow(2, n)) % mod;
    DEBUG printf("\t%lld\n", ways);
    printf("%lld\n", ans);
  }
  return 0;
}
