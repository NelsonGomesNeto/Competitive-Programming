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

const int maxN = 100;
int n, a, b, p, q;
lli invP, invQ;

lli memo[maxN][maxN][2];
lli solve(int ta = a, int ao = b, bool taTurn = true)
{
  if (ta >= n) return 1;
  if (ao >= n) return 0;
  lli& ans = memo[ta][ao][taTurn];
  if (ans != -1) return ans;

  ans = 0;
  if (taTurn)
  {
    for (int i = 1; i <= p; ++i)
      ans = (ans + solve(ta + i, ao, false) * invP % mod) % mod;
  }
  else
  {
    for (int i = 1; i <= q; ++i)
      ans = (ans + solve(ta, ao + i, true) * invQ % mod) % mod;
  }

  return ans;
}

int main()
{
  while (~scanf("%d %d %d %d %d", &n, &a, &b, &p, &q))
  {
    invP = inv(p), invQ = inv(q);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
