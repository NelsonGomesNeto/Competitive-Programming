#include <bits/stdc++.h>
#define lli long long int

lli gcd(lli a, lli b)
{
  if (!b) return(a);
  return(gcd(b, a % b));
}

int main()
{
  lli a, b;
  while (scanf("%lld %lld", &a, &b) != EOF)
    printf("gcd(%lld , %lld) = %lld\n", a, b, gcd(a, b));
  return(0);
}
