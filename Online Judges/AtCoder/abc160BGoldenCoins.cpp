#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli x;
  while (scanf("%lld", &x) != EOF)
  {
    lli ans = 1000LL * (x / 500LL);
    x = x % 500;
    ans += x / 5LL * 5LL;
    printf("%lld\n", ans);
  }
  return 0;
}