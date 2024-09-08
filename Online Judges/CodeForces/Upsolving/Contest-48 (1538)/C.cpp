#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli l, r;
lli a[maxN];
vector<lli> as;
lli cnt[maxN], acc[maxN + 1];

int binarySearch(lli target, bool upperBound = false)
{
  int lo = 0, hi = as.size() - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (as[mid] <= target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (as[mid] >= target) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}

bool valid(lli num)
{
  return num >= l && num <= r;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld %lld", &n, &l, &r);
    as.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      as.push_back(a[i]);
    }
    sort(as.begin(), as.end());
    as.resize(distance(as.begin(), unique(as.begin(), as.end())));

    for (int i = 0; i < as.size(); i++)
      cnt[i] = 0;
    for (int i = 0; i < n; i++)
      cnt[lower_bound(as.begin(), as.end(), a[i]) - as.begin()]++;
    for (int i = 0; i < as.size(); i++)
      acc[i + 1] = acc[i] + cnt[i];

    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      // a[i] + a[j] >= l
      // a[j] >= l - a[i]
      // a[i] + a[j] <= r
      // a[j] <= r - a[i]
      lli loTarget = l - a[i];
      lli hiTarget = r - a[i];

      int loPos = binarySearch(loTarget);
      int hiPos = binarySearch(hiTarget, true);
      DEBUG printf("%lld - %lld - %lld\n", a[i], as[loPos], as[hiPos]);
      if (valid(a[i] + as[loPos]) && valid(a[i] + as[hiPos]))
        ans += acc[hiPos + 1] - acc[loPos];
      if (valid(a[i] + a[i]))
        ans -= 1;
    }
    ans >>= 1LL;
    printf("%lld\n", ans);
  }
  return 0;
}
