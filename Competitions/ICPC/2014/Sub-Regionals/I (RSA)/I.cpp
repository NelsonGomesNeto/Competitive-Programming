#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli N, E, C, M;

lli modPow(lli x, lli y, lli mod)
{
  if (y == 0) return(1);
  lli ret = modPow(x, y >> 1, mod);
  ret = (ret * ret) % mod; if (y & 1) ret = (ret * x) % mod;
  return(ret);
}

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
  while (scanf("%lld %lld %lld", &N, &E, &C) != EOF)
  {
    for (lli k = 2, end = sqrt(N); k <= end; k ++)
      if (N % k == 0)
      {
        lli P = k, Q = N / k;
        lli totient = (P - 1) * (Q - 1);
        lli D = modInverse(E, totient);
        M = modPow(C, D, N);
        // printf("%lld %lld %lld || %lld %lld | %lld (%lld) | %lld | %lld\n", N, E, C, P, Q, totient, gcd(totient, E), D, M);
        printf("%lld\n", M);
        break;
      }
  }

  return(0);
}