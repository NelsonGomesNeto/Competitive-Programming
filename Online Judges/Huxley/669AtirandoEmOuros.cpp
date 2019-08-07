#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxR = 1e6;
set<lli> lines, columns; lli n; int r;
lli lin[maxR]; int linSize;

int upperBound(lli target, int lo = 0, int hi = linSize - 1)
{
  if (linSize == 0) return(0);
  while (lo < hi)
  {
    int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
    if (target >= lin[mid]) lo = mid;
    else hi = mid - 1;
  }
  return(lin[lo] > target ? lo - 1 : lo);
}
int lowerBound(lli target, int lo = 0, int hi = linSize - 1)
{
  if (linSize == 0) return(1);
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (target <= lin[mid]) hi = mid;
    else lo = mid + 1;
  }
  return(lin[lo] < target ? lo + 1 : lo);
}

int getRange(lli v)
{
  // return(upper_bound(lin, lin+linSize, n + 1 + (v >> 1)) - lower_bound(lin, lin+linSize, n + 1 - (v >> 1)));
  return(upperBound(n + 1 + (v >> 1)) - lowerBound(n + 1 - (v >> 1)) + 1);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%lld %d", &n, &r);
    lli ans = 2LL*(n*n) + 2LL*n + 1LL;

    lines.clear(), columns.clear();
    for (int i = 0; i < r; i ++)
    {
      int op; lli c; scanf("%d %lld", &op, &c);
      if (op == 0) lines.insert(c);
      else columns.insert(c);
    }

    linSize = 0;
    for (lli c: lines)
    {
      lli v = 2LL*n + 1 - 2LL*(c <= n + 1 ? n + 1 - c : c - (n + 1));
      ans -= v;
      lin[linSize ++] = c;
    }
    for (lli c: columns)
    {
      lli v = 2LL*n + 1 - 2LL*(c <= n + 1 ? n + 1 - c : c - (n + 1));
      ans -= v - getRange(v);
    }

    // printf("%lld %d - %lld\n", n, r, ans);
    printf("%lld\n", ans);
  }
  return(0);
}