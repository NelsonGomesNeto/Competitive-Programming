#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli x;
list<pair<lli, lli>> a;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &x);
    a.clear();
    for (int i = 0; i < n; i++)
    {
      lli v; scanf("%lld", &v);
      a.push_back({1, v});
    }

    lli ans = 0;
    for (auto &[cnt, value]: a)
    {
      if (value % x != 0)
        break;

      a.push_back({cnt * x, value / x});
    }
    for (auto &[cnt, value]: a)
    {
      DEBUG printf("\t%lld %lld\n", cnt, value);
      ans += value * cnt;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
