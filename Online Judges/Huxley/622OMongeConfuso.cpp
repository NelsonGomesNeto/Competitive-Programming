#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 50; int n;
const lli mod = 1e9 + 7;
lli a[maxN];

lli modGCD()
{
  lli ans = a[0];
  for (int i = 1; i < n; i ++)
    ans = __gcd(ans, a[i]);
  return(ans);
}

lli modMult()
{
  lli ans = a[0];
  for (int i = 1; i < n; i ++)
    ans = (ans * a[i]) % mod;
  return(ans);
}

lli modPow(lli x, lli y)
{
  if (!y) return(1);
  lli ret = modPow(x, y >> 1);
  ret = (ret * ret) % mod; if (y & 1) ret = (ret * x) % mod;
  return(ret);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);

  printf("%lld\n", modPow(modMult(), modGCD()));

  return(0);
}