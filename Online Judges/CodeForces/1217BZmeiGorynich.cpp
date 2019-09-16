#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n; lli x;
const lli inf = 1e9 + 10;
struct Blow
{
  lli d, h;
  void read() { scanf("%lld %lld", &d, &h); }
  bool operator<(const Blow &other) const
  {
    return (d - h) > (other.d - other.h);
  }
};
Blow blows[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %lld", &n, &x);
    lli strongest = 0;
    for (int i = 0; i < n; i ++)
    {
      blows[i].read();
      strongest = max(strongest, blows[i].d);
    }
    sort(blows, blows+n);

    lli lo = 0, hi = inf;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1LL;
      if (strongest >= x - max(0LL, mid*(blows[0].d - blows[0].h))) hi = mid;
      else lo = mid + 1;
    }
    printf("%lld\n", lo == inf ? -1LL : lo + (x - lo*(blows[0].d - blows[0].h) > 0));
  }
  return(0);
}