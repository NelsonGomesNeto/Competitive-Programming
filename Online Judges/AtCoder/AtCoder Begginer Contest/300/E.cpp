#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

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

const lli inv5 = inv(5);

lli n;

unordered_map<lli, lli> memo;
lli solve(lli a = 1)
{
  if (a >= n) return a == n;
  if (memo.count(a)) return memo[a];
  lli& ans = memo[a];

  ans = 0;
  for (int i = 2; i <= 6; ++i)
    ans = (ans + solve(a * i) * inv5 % mod) % mod;

  return ans;
}

int main()
{
  while (~scanf("%lld", &n))
  {
    memo.clear();
    lli ans = solve() % mod;
    printf("%lld\n", ans);
  }
  return 0;
}
