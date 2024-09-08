#include <bits/stdc++.h>
#define lli long long int
// sum (i = 0 to n - 1) 10^i * x
// gp sum: S_n = a_1 * (1 - r^n) / (1 - r)
lli mod = 1e9 + 7;

lli fpow(lli x, lli y)
{
  if (!y) return(1);
  lli ret = fpow(x, y >> 1);
  ret = (ret * ret) % mod;
  if (y & 1) ret = (ret * x) % mod;
  return(ret);
}

lli gpSum(lli a1, double r, lli n)
{
  lli inv = fpow(r - 1, mod - 2);
  return(a1 * (fpow(r, n) - 1 + mod) % mod * inv % mod);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli n, m; scanf("%lld %lld", &n, &m);
    if (m == 0) printf("0\n");
    else printf("%lld\n", gpSum(m, fpow(10, floor(log10(m)) + 1), n));
  }
  return(0);
}
