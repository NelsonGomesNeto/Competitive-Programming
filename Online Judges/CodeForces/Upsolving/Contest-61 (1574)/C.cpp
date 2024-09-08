#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
lli a[maxN], acc[maxN + 1];
lli x[maxN], y[maxN];

int binarySearch(bool upperBound, int target, int lo = 0, int hi = n - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (a[mid] <= target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (a[mid] >= target) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}

lli calc(int pos, int i)
{
  if (pos < 0 || pos >= n) return LONG_LONG_MAX;

  lli req = 0;
  if (a[pos] < x[i]) req += x[i] - a[pos];
  lli total = acc[n] - a[pos];
  if (total < y[i]) req += y[i] - total;
  return req;
}
lli eval(lli s, int i)
{
  lli req = 0;
  if (s < x[i]) req += x[i] - s;
  lli total = acc[n] - s;
  if (total < y[i]) req += y[i] - total;
  return req;
}

/*
  (x[i] - s) + (y[i] - (total - s))
  (x[i] - s) + (y[i] - total + s)
  x[i] + y[i] - total
*/

int main()
{
  while (~scanf("%d" , &n))
  {
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    sort(a, a+n);
    for (int i = 0; i < n; i++) acc[i + 1] = acc[i] + a[i];

    scanf("%d", &m);
    for (int i = 0; i < m; i++) scanf("%lld %lld", &x[i], &y[i]);

    for (int i = 0; i < m; i++)
    {
      lli ans = min({
        calc(binarySearch(false, x[i]) - 1, i),
        calc(binarySearch(false, x[i]), i),
        calc(binarySearch(false, x[i]) + 1, i),

        calc(binarySearch(true, x[i]) - 1, i),
        calc(binarySearch(true, x[i]), i),
        calc(binarySearch(true, x[i]) + 1, i)
      });

      lli lo = 1, hi = 1e12;
      while (lo < hi - 5)
      {
        lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
        lli elo = eval(midlo, i), ehi = eval(midhi, i);
        if (elo < ehi) hi = midhi;
        else lo = midlo;
      }
      for (lli j = lo; j <= hi; j++)
      {
        ans = min({
          ans,
          calc(binarySearch(false, j) - 1, i),
          calc(binarySearch(false, j), i),
          calc(binarySearch(false, j) + 1, i),

          calc(binarySearch(true, j) - 1, i),
          calc(binarySearch(true, j), i),
          calc(binarySearch(true, j) + 1, i),
        });
      }

      if (a[n - 1] >= x[i]) ans = min(ans, max(0LL, x[i] + y[i] - acc[n]));
      printf("%lld\n", ans);
    }
  }
  return 0;
}
