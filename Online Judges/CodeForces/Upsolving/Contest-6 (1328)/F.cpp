#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
lli a[maxN];

lli eval(lli x)
{
  map<lli, int> cnt;
  for (int i = 0; i < n; i++)
  {
    if (!cnt.count(a[i]))
      cnt[a[i]] = 0;
    if (++cnt[a[i]] >= k)
      return 0;
  }

  lli ans = 0;
  for (int i = 0; i < n; i++)
  {
    lli lo = cnt.begin()->first, hi = cnt.rbegin()->first;
    lli dlo = abs(lo - x), dhi = abs(hi - x);
    if ((dlo <= dhi && lo != x) || hi == x)
    {
      cnt.begin()->second--;
      cnt[x]++, ans += dlo;
      if (cnt[x] >= k)
        return ans;
      if (cnt.begin()->second == 0)
        cnt.erase(cnt.begin());
    }
    else
    {
      cnt.rbegin()->second--;
      cnt[x]++, ans += dhi;
      if (cnt[x] >= k)
        return ans;
      if (cnt.rbegin()->second == 0)
        cnt.erase(cnt.rbegin()->first);
    }
  }
  return ans;
}
lli ternarySearch(lli lo = 1, lli hi = 1e9)
{
  while (lo < hi - 3)
  {
    lli midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    lli elo = eval(midlo), ehi = eval(midhi);
    if (elo <= ehi) hi = midhi;
    else lo = midlo;
  }
  lli ans = eval(lo);
  while (++lo < hi)
    ans = min(ans, eval(lo));
  return ans;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    sort(a, a+n);

    lli ans = ternarySearch();
    printf("%lld\n", ans);
  }
  return 0;
}
