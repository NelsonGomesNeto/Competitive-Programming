#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli n, m, a; scanf("%lld %lld %lld", &n, &m, &a);
  printf("%lld\n", (((n % a) > 0) + (n / a)) * (((m % a) > 0) + (m / a)));
  return(0);
}