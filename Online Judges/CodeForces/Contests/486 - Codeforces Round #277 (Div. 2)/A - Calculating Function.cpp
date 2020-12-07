#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli n; scanf("%lld", &n);
  printf("%lld\n", ((n / 2) + (n & 1)) * (n & 1 ? -1 : 1));
  return(0);
}