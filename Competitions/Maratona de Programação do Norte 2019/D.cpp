#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  ans = fib(n) * n! * 2^n
*/

lli mod = 1e9 + 7;
lli fib(lli n)
{
  lli a = 1, b = 1;
  for (int i = 0; i < n; i ++)
  {
    lli aux = b;
    b = (a + b) % mod;
    a = aux;
  }
  return(a);
}
lli fact(lli n)
{
  lli ans = 1;
  for (int i = 1; i <= n; i ++) ans = (ans * i) % mod;
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
  lli n; scanf("%lld", &n);
  printf("%lld\n", ((fib(n) * fact(n) % mod) * modPow(2, n)) % mod);
  return(0);
}