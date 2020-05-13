#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int k;
  while (scanf("%d", &k) != EOF)
  {
    lli ans = 0;
    for (int i = 1; i <= k; i++)
      for (int j = 1; j <= k; j++)
        for (int m = 1; m <= k; m++)
        {
          ans += gcd(i, gcd(j, m));
          // printf("\t%d %d %d - %d\n", i, j, m, gcd(i, gcd(j, m)));
        }
    printf("%lld\n", ans);
  }
  return 0;
}