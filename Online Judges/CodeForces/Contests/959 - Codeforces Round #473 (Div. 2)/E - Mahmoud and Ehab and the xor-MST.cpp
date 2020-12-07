#include <bits/stdc++.h>
#define lli long long int

lli calculate(lli n)
{
  lli count = 1;
  while (n > 0)
  {
    printf("%lld %lld\n", n, count);
    count *= !(n & 1) ? 2 : 1;
    n /= 2;
  }
  return(count);
}

int main()
{
  lli n; scanf("%lld", &n);
  if (!(n & 1)) printf("1\n");
  else printf("%lld\n", calculate(n - 1));
  return(0);
}