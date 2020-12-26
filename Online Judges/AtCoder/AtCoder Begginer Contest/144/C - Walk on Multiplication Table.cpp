#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n; scanf("%lld", &n);
  lli ans = 1e18;
  for (lli i = 1, end = sqrt(n); i <= end; i ++)
    if (n % i == 0)
      ans = min(ans, i + (n / i) - 2);
  printf("%lld\n", ans);
  return 0;
}