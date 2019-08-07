#include <bits/stdc++.h>
#define lli long long int
// inv = pow(r, mod - 2) (since mod is prime)

lli modInverse(lli a, lli mod)
{
  lli m0 = mod;
  lli y = 0, x = 1;
  if (mod == 1) return(0);
  while (a > 1)
  {
    lli q = a / mod;
    lli t = mod;
    mod = a % mod, a = t;
    t = y;
    y = x - q * y;
    x = t;
  }
  if (x < 0) x += m0;
  return(x);
}

int main()
{
  lli x, mod;
  while (scanf("%lld %lld", &x, &mod) != EOF)
    printf("modInverse(%lld, %lld) = %lld\n", x, mod, modInverse(x, mod));

  return(0);
}