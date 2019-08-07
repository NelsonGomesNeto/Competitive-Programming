#include <bits/stdc++.h>
#define lli long long int

lli apSum(lli a, lli b, lli r)
{
  return((a + b) * (b - a + 1) * r / 2);
}

int main()
{
  lli n;
  while (scanf("%lld", &n) && n >= 0)
  {
    lli sum = 1 + apSum(1, n, 1);
    printf("%lld\n", sum);
  }
  return(0);
}
// 0 1
// 1 2
// 2 4
// 3 7
// 4 11
// 5 16