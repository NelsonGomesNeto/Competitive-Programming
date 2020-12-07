#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli n, p;

lli ones(lli num)
{
  lli o = 0;
  while (num)
  {
    o += num & 1LL;
    num /= 2;
  }
  return o;
}

int main()
{
  while (scanf("%lld %lld", &n, &p) != EOF)
  {
    int ans = 1;
    for (; ans < 1e4; ans ++)
    {
      lli x = n - ans * p;
      if (ones(x) <= ans && ans <= x)
        break;
    }
    printf("%d\n", ans == 1e4 ? -1 : ans);
  }
  return 0;
}
