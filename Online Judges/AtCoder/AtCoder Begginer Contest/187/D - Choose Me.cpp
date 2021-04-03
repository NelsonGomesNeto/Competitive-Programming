#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
struct City
{
  lli a, b;
  bool operator<(const City &other) const { return 2*a + b > 2*other.a + other.b; }
};
City cities[maxN];
lli a[maxN], b[maxN];

bool can(int x)
{
  lli ans = 0;
  for (int i = 0; i < x; i++)
    ans += cities[i].a + cities[i].b;
  for (int i = x; i < n; i++)
    ans -= cities[i].a;
  return ans > 0;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld %lld", &a[i], &b[i]);
    for (int i = 0; i < n; i++)
      cities[i] = City{a[i], b[i]};
    sort(cities, cities+n);

    int lo = 0, hi = n;
    while (lo < hi)
    {
      int mid = (lo + hi) >> 1;
      if (can(mid)) hi = mid;
      else lo = mid + 1;
    }
    printf("%d\n", lo);
  }
  return 0;
}