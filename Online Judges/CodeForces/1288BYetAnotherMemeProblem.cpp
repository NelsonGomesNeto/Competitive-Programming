#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b;

bool valid(lli aa, lli bb)
{
  lli pot = ceil(log10(bb));
  return aa*bb + aa + bb == aa * pow(10, pot) + bb;
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%lld %lld", &a, &b);
    DEBUG {
      printf("%lld %lld\n", a, b);
      lli ans = 0;
      for (int i = 1; i <= a; i ++)
        for (int j = 1; j <= b; j ++)
          if (valid(i, j))
          {
            printf("\t%d %d\n", i, j);
            ans ++;
          }
      printf("\t%lld\n", ans);
    }

    lli pot = floor(log10(b + 1));
    printf("%lld\n", a * pot);
  }
  return 0;
}
