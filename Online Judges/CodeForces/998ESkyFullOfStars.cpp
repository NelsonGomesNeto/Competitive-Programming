#include <bits/stdc++.h>
#define lli long long int
lli mod = 998244353;

lli pot(lli x, lli n)
{
  if (!n) return(1);
  lli ret = pot(x, n / 2);
  ret = (ret * ret) % mod;
  if (n & 1) return((ret * x) % mod);
  return(ret);
}

int main()
{
  int n; scanf("%d", &n);
  lli ans = 3 * (pot(3, n * (n - 1)) - 3) * 2 * 2 - 9;

  printf("%lld\n", ans);

  return(0);
}