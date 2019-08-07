#include <bits/stdc++.h>
#define lli long long int

// an = a1 + (n - 1)*q)
lli apSum(lli a1, lli an, lli n)
{
  return(n * (a1 + an) / 2.0);
}

int main()
{
  lli a1, an, n;
  while (scanf("%lld %lld %lld", &a1, &an, &n) != EOF)
    printf("[%lld, %lld, %lld] = %lld\n", a1, an, n, apSum(a1, an, n));
  return(0);
}