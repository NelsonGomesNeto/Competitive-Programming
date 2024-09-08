#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Item
{
  lli weight, volume, value;
  int read() { return ~scanf("%lld %lld %lld", &weight, &volume, &value); }
};
const int maxN = 2e5; int n;
Item items[maxN];

ldouble f(const Item& item)
{
  ldouble x = 1e30;
  ldouble times = min(item.volume, item.weight);
  return times / item.value;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      items[i].read();

    ldouble ans = 0;
    for (int i = 0; i < n; ++i)
      ans = max(ans, f(items[i]));
    printf("%.15Lf\n", ans);
  }
  return 0;
}
