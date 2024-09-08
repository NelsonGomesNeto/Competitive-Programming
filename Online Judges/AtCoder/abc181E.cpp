#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
const lli inf = 1e18;
lli h[maxN], w[maxN];
lli l[maxN + 1], r[maxN + 1];

int binarySearch(bool upperBound, int x, int lo = 0, int hi = n - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (h[mid] <= x) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (x <= h[mid]) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++) scanf("%lld", &h[i]);
    for (int i = 0; i < m; i++) scanf("%lld", &w[i]);

    sort(h, h+n);
    DEBUG
      for (int i = 0; i < n; i++)
        printf("%lld%c", h[i], i < n - 1 ? ' ' : '\n');

    for (int i = 1; i < n; i+=2)
    {
      l[i] = l[i - 1] + (h[i] - h[i - 1]);
      if (i + 1 < n) l[i + 1] = l[i];
    }
    r[n - 1] = 0;
    for (int i = n - 2; i >= 0; i-=2)
    {
      r[i] = r[i + 1] + (h[i + 1] - h[i]);
      if (i - 1 >= 0) r[i - 1] = r[i];
    }

    lli ans = inf;
    for (int i = 0; i < m; i++)
    {
      vector<int> pos = {binarySearch(false, w[i]), binarySearch(true, w[i])};
      for (int j = 0; j < 2; j++)
      {
        int p = pos[j];
        DEBUG printf("%lld - %d (%lld) | %lld %lld %lld\n", w[i], p, h[p], l[max(0, p - 1)], r[min(n - 1, p + 1)], abs(w[i] - h[p]));
        lli val = l[max(0, p - 1)] + r[min(n - 1, p + 1)] + abs(w[i] - h[p]);
        if (p & 1)
          val += h[p + 1] - h[p - 1];
        ans = min(ans, val);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}