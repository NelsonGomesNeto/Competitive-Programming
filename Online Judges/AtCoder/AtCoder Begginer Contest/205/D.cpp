#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
lli a[maxN];
struct Range
{
  lli lo, hi; lli initial, total;
};
vector<Range> b;

int binarySearch(lli target, int lo = 0, int hi = b.size() - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (b[mid].initial <= target) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    b.clear();
    if (a[0] > 1)
      b.push_back(Range{1, 1 + (a[0] - 1), 1, a[0] - 1});
    for (int i = 0; i + 1 < n; i++)
    {
      if (a[i] + 1 == a[i + 1]) continue;
      b.push_back(Range{a[i] + 1, a[i] + 1 + a[i + 1] - (a[i] + 1), b.back().total + 1, b.back().total + (a[i + 1] - (a[i] + 1))});
    }
    if (b.empty()) b.push_back(Range{a[n - 1] + 1, (lli)1e18 + (lli)1e5 + 1LL, 1, LONG_LONG_MAX});
    else b.push_back(Range{a[n - 1] + 1, (lli)1e18 + (lli)1e5 + 1LL, b.back().total + 1, LONG_LONG_MAX});

    while (q--)
    {
      lli k; scanf("%lld", &k);
      int pos = binarySearch(k);
      DEBUG printf("%lld %lld | %lld %lld\n", b[pos].lo, b[pos].hi, b[pos].initial, b[pos].total);
      lli ans = b[pos].lo + (k - b[pos].initial);
      printf("%lld\n", ans);
    }
  }
  return 0;
}