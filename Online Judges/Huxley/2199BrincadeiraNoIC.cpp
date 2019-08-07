#include <stdio.h>
#define lli long long int

lli fact(lli n)
{
  if (n <= 1) return(1);
  return(n * fact(n - 1));
}

lli log3(lli n)
{
  if (n < 3) return(0);
  return(1 + log3(n / 3));
}

lli y(lli n)
{
  return(fact(log3(n)));
}

int main()
{
  lli n; scanf("%lld", &n);
  printf("%lld\n", y(n));
  return(0);
}