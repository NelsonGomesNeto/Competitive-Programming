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
    lli l = 2;
    for (int i = 3; i <= n; i++)
      l = lcm(l, i);
    ans = l + 1;
    printf("%lld\n", ans);
  }

  return 0;
}