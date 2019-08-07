#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli n, a, b, c, d; scanf("%lld %lld %lld %lld %lld", &n, &a, &b, &c, &d);
  lli dist = abs(c - a) + abs(d - b);
  lli possibilities = n >= dist;
  if (possibilities)
  {
    lli lol = n - dist;
    possibilities += lol / 2;
  }
  if (a == c && b == d)
    printf("%lld\n", n / 2);
  else
    printf("%lld\n", possibilities);
  return(0);
}