#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    lli ans = 0;
    for (int i = 1; i <= n; i++)
      if (!(i % 3 == 0 || i % 5 == 0))
        ans += i;
    printf("%lld\n", ans);
  }
  return 0;
}