#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli euclidesGcd(lli a, lli b)
{
  if (!b) return(a);
  return(euclidesGcd(b, a % b));
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli a, b, c, d; scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
    lli x = abs(c - a), y = abs(d - b);
    lli ans = euclidesGcd(max(x, y), min(y, x));
    printf("%lld\n", ans + 1);
  }
  return(0);
}