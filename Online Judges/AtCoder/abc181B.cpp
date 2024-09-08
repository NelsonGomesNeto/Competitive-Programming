#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n;
lli apSum(lli a1, lli an, lli n)
{
  return(n * (a1 + an) / 2.0);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      lli a, b; scanf("%lld %lld", &a, &b);
      ans += apSum(a, b, b - a + 1);
    }
    printf("%lld\n", ans);
  }
  return 0;
}