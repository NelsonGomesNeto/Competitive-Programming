#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli pot(lli n)
{
  lli ans = 0;
  while (n) ans ++, n >>= 1;
  return(ans);
}

int main()
{
  lli n; scanf("%lld", &n);

  // lli ans = 0;
  // for (int i = 1; i <= n; i ++)
  // {
  //   bool eveneven = true;
  //   for (int j = 2, end = sqrt(i) + 1; j <= i; j ++)
  //     if (i % j == 0 && j & 1)//((j & 1) || ((i / j) & 1)))
  //       eveneven = false;
  //   ans += eveneven;
  //   if (ans != pot(i))
  //     printf("FUDEU %lld %lld\n", ans, pot(i));
  // }
  // printf("%lld\n", ans);
  printf("%lld\n", pot(n));
  // printf("%lld\n", (lli) floor(log2(n)) + 1);

  return(0);
}