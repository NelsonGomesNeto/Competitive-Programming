#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli coins[11];
lli p;

int main()
{
  coins[0] = 1;
  for (int i = 1; i <= 10; i++)
    coins[i] = i * coins[i - 1];

  while (~scanf("%lld", &p))
  {
    lli ans = 0;
    for (int i = 10; i >= 1; i--)
    {
      lli needed = min(100LL, p / coins[i]);
      ans += needed;
      p -= coins[i] * needed;
    }
    assert(p == 0);
    printf("%lld\n", ans);
  }
  return 0;
}