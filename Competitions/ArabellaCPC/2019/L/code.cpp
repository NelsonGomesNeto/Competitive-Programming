#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1e9 + 7;

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
lli modApSum(lli a1, lli n, lli d)
{
  lli an = (a1 + (n - 1 + mod) % mod * d % mod) % mod;
  return n * (a1 + an) % mod * inv(2) % mod;
}

lli calcCycleSize(lli n, lli x)
{
  lli g = gcd(n, x);
  if (g == 1) return n;
  if (g == n) return 1;
  return g;
}

lli n, m, r, c;
lli mat(lli rr, lli cc)
{
  rr %= n, cc %= m;
  return (1 + rr * m % mod + cc) % mod;
}

int main()
{
  while (~scanf("%lld %lld %lld %lld", &n, &m, &r, &c))
  {
    lli csn = calcCycleSize(n, r); // vertical cycle size
    lli csm = calcCycleSize(m, c); // horizontal cycle size
    lli cs = lcm(csn, csm); // total cycle size
    DEBUG printf("\t%lld %lld - %lld %lld - %lld %lld - %lld\n", n, m, r, c, csn, csm, cs);

    lli si = 0, sj = m - 1;

    // for (int i = 0; i < n; i++)
    //   for (int j = 0; j < m; j++)
    //     printf("%lld%c", mat(i, j), j < m - 1 ? ' ' : '\n');
    // lli lo = 0, hi = r - 1;
    lli delta = (mat(r, c) - mat(0, 0) + mod) % mod;
    lli ans = modApSum(mat(si, sj), cs, delta);

    printf("%lld\n", ans);
  }
  return 0;
}