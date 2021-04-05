#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli gcdSum(lli a)
{
  lli sum = 0, aux = a;
  while (aux)
  {
    sum += aux % 10;
    aux /= 10;
  }
  return gcd(a, sum);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli n; scanf("%lld", &n);
    while (gcdSum(n) == 1)
      n++;
    printf("%lld\n", n);
  }
  return 0;
}
