#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli c;
vector<lli> days;
map<lli, lli> in, out, daily;
struct Service
{
  lli lo, hi, x;
  void read()
  {
    scanf("%lld %lld %lld", &lo, &hi, &x);
    if (lo == hi)
    {
      if (!daily.count(lo)) daily[lo] = 0;
      daily[lo] += x;
    }

    days.push_back(lo), days.push_back(hi);
    if (!in.count(lo)) in[lo] = 0;
    if (!in.count(hi)) in[hi] = 0;
    in[lo] += x;
    if (!out.count(hi)) out[hi] = 0;
    if (!out.count(lo)) out[lo] = 0;
    out[hi] += x;
  }
};
Service services[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &c))
  {
    days.clear(), in.clear(), out.clear(), daily.clear();
    for (int i = 0; i < n; i++)
      services[i].read();
    sort(days.begin(), days.end());
    days.resize(distance(days.begin(), unique(days.begin(), days.end())));

    lli ans = 0, curr = 0;
    for (int i = 0; i < days.size(); i++)
    {
      lli d = days[i];

      curr += in[d];
      lli now = curr;
      curr -= out[d];
      lli after = curr;

      lli onlyNow = now;
      ans += min(c, onlyNow);
      DEBUG printf("%d - %lld - %lld %lld\n", i, d, now, after);

      if (i + 1 < days.size())
      {
        lli nd = days[i + 1];
        lli dist = (nd - 1) - (d + 1) + 1;
        ans += dist * min(c, after);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}