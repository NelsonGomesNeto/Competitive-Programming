#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n, nsz;

bool can(int first, int last, int sz, int mid)
{
  int res = first * pow(10, sz) + mid * 10 + last;
  DEBUG printf("\t%d %d %d %d: %d\n", first, last, sz, mid, res);
  return first * pow(10, sz) + mid * 10 + last <= n;
}
int binarySearch(int first, int last, int sz, int lo, int hi)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (can(first, last, sz, mid)) lo = mid;
    else hi = mid - 1;
  }
  if (!can(first, last, sz, lo)) return 0;
  return lo + 1;
}

int cnt(int first, int last, int sz)
{
  int ans = (first==last)*(first <= n) + (first * 10 + last <= n);
  DEBUG printf("\t%d %d - %d", first, last, ans);
  for (int i = 2; i <= nsz; i ++)
    ans += binarySearch(first, last, i, 0, pow(10, i - 1) - 1);
  DEBUG printf(" - %d\n", ans);
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    nsz = log10(n);
    lli ans = 0;
    for (int a = 1; a <= n; a ++)
    {
      if (a % 10 == 0) continue;
      int sz = log10(a);
      DEBUG printf("%d\n", a);
      ans += cnt(a % 10, a / pow(10, sz), sz);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
/*
a = y---x
b = x---y
*/