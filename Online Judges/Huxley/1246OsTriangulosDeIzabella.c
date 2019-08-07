#include <stdio.h>
#define lli long long int

lli apSum(lli a, lli b, lli q)
{
  return((long double) (a + b) / 2 * (b - a + 1) * q);
}

int main()
{
  int n; scanf("%d", &n);
  while (n --)
  {
    int k; scanf("%d", &k);
    lli firstLine = 1 + apSum(1, k - 1, 1);
    printf("%lld\n", apSum(firstLine, firstLine + k - 1, 1));
  }
  return(0);
}
// PA sum: s_n = (a_1 + a_n) / 2 * ((a_n - a_1 + 1) * q)