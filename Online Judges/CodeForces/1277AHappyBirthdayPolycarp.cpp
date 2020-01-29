#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli n; scanf("%lld", &n);
    int ans = 0;
    for (int i = 0; i < 10; i ++)
      for (int j = 1; j < 10; j ++)
      {
        lli num = 0;
        for (int k = 0; k <= i; k ++)
          num += j * pow(10, k);
        if (num <= n) ans ++;
      }
    printf("%d\n", ans);
  }
  return 0;
}
