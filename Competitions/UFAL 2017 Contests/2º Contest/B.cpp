#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int
lli mod = (1e9 + 7);

lli pot(lli x, lli n)
{
  lli res = 1;
  while (n > 0)
  {
    if (n & 1) res = (res * x) % mod;
    n /= 2;
    x = (x * x) % mod;
  }
  return(res);
}

lli pot2(lli x, lli n)
{
  if (n == 0) return(1);
  if (n == 1) return(x);
  if (n & 1)
  {
    lli half = pot(x, (n - 1) / 2);
    return((((half * half) % mod) * x) % mod);
  }
  else
  {
    lli half = pot(x, n / 2);
    return((half * half) % mod);
  }
}

lli pgSum(lli a1, lli r, lli n)
{ /* Sn = a1 * (r^n - 1) / (r - 1) */
  lli inv = pot(r - 1, mod - 2); // Since mod is prime
  lli sn = (((a1 * (pot(r, n) - 1)) % mod) * inv) % mod;
  DEBUG printf("%lld %lld %lld %lld\n", a1, r, sn, pot(r, n));
  return(sn);
}

int main()
{
  char digit[(int) 1e5 + 2];
  lli at[(int) 1e5], k, size = 0;
  scanf("%s\n%lld", digit, &k);
  for (int i = 0; digit[i]; i ++)
    at[size ++] = digit[i] == '0' || digit[i] == '5';

  lli total = 0;
  for (int i = 0; i < size; i ++)
  {
    lli a1 = pot(2, i), r = pot(2, size);
    if (at[i])
      total = (total + pgSum(a1, r, k)) % mod;
  }

  printf("%lld\n", total);

  return(0);
}