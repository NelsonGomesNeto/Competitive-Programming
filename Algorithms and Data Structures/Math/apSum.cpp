#include <bits/stdc++.h>
#define lli long long int

lli apSum(lli a1, lli n, lli d)
{
  lli an = a1 + (n - 1)*d;
  return n * (a1 + an) >> 1LL;
}

// an = a1 + (n - 1)*q)
lli apSum(lli a1, lli an, lli n)
{
  return(n * (a1 + an) / 2.0);
}

// lli apSum(lli a1, lli n, lli q)
// {
//   return (a1+a1+(n-1)*q)*n / 2LL;
// }

int main()
{
  lli a1, an, n;
  while (scanf("%lld %lld %lld", &a1, &an, &n) != EOF)
    printf("[%lld, %lld, %lld] = %lld\n", a1, an, n, apSum(a1, an, n));
  return(0);
}