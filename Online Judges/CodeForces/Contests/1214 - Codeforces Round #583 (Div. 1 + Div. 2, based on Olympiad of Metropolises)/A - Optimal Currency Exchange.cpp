#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  lli n, d, e;
  while (scanf("%lld %lld %lld", &n, &d, &e) != EOF)
  {
    lli ans = n % d;
    while (n > 0)
    {
      n -= 5LL*e;
      if (n >= 0) ans = min(ans, n % d);
    }

    printf("%lld\n", ans);
  }
  return(0);
}
