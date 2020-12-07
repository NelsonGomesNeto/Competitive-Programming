#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli k;
lli a[maxN];

lli evaluate(lli low, lli high)
{
  lli cost = 0;
  for (int i = 0; i < n && a[i] < low; i ++)
    cost += low - a[i];
  for (int i = n - 1; i >= 0 && a[i] > high; i --)
    cost += a[i] - high;
  return cost;
}
bool can(lli diff)
{
  lli lo = 1, hi = 1e9;
  while (lo < hi - 2)
  {
    lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    lli elo = evaluate(midlo, midlo + diff), ehi = evaluate(midhi, midhi + diff);
    if (elo <= ehi) hi = midhi;
    else lo = midlo;
  }
  lli ans = 1e18;
  for (int i = lo; i <= hi; i ++)
    ans = min(ans, evaluate(i, i + diff));
  return ans <= k;
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    sort(a, a+n);

    lli lo = 0, hi = 1e9;
    while (lo < hi)
    {
      lli mid = (lo + hi) >> 1LL;
      if (can(mid)) hi = mid;
      else lo = mid + 1;
    }
    printf("%lld\n", lo);
  }
  return 0;
}
