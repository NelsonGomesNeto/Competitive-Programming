#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 5e3; int n;
struct Test
{
  lli day, minDay;
  bool operator<(const Test &a) const { return(day < a.day || (day == a.day && minDay < a.minDay)); }
};
Test tests[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%lld %lld", &tests[i].day, &tests[i].minDay);
  sort(tests, tests+n);
  lli did = tests[0].minDay;
  for (int i = 1; i < n; i ++)
  {
    if (tests[i].minDay < did)
      did = tests[i].day;
    else
      did = tests[i].minDay;
  }
  printf("%lld\n", did);
  return(0);
}