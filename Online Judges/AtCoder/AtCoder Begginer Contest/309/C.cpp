#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5;
int n; lli k;
pair<lli, lli> pills[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &k))
  {
    lli total = 0;
    for (int i = 0; i < n; ++i)
    {
      scanf("%lld %lld", &pills[i].first, &pills[i].second);
      total += pills[i].second;
    }

    sort(pills, pills+n);
    lli ans = -1;
    if (total <= k) ans = 1;
    else
    {
      for (int i = 0; i < n; ++i)
      {
        total -= pills[i].second;
        DEBUG printf("%lld %lld\n", pills[i].first, total);
        if (total <= k)
        {
          ans = pills[i].first + 1;
          break;
        }
      }
    }

    printf("%lld\n", ans);
  }
  return 0;
}
