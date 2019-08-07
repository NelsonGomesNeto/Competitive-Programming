#include <bits/stdc++.h>
#define lli long long int

int nearlyLucky(lli n)
{
  lli count = 0;
  while (n > 0)
  {
    count += (n % 10 == 4 || n % 10 == 7);
    n /= 10;
  }
  if (!count) return(0);
  while (count > 0)
  {
    if (count % 10 != 4 && count % 10 != 7) return(0);
    count /= 10;
  }
  return(1);
}

int main()
{
  lli n; scanf("%lld", &n);
  printf("%s\n", nearlyLucky(n) ? "YES" : "NO");
  return(0);
}