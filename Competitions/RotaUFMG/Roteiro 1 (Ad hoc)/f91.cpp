#include <bits/stdc++.h>
#define lli long long int

lli f91(lli n)
{
  if (n <= 100) return(f91(f91(n + 11)));
  else return(n - 10);
}

int main()
{
  lli n;
  while (scanf("%lld", &n) && n)
    printf("f91(%lld) = %lld\n", n, f91(n));

  return(0);
}