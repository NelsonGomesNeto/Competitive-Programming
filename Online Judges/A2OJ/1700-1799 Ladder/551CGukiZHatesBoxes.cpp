#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
lli a[maxN], aux[maxN], sum, auxSum;

bool can(lli x)
{
  memcpy(a, aux, sizeof(aux)), sum = auxSum;
  for (lli i = 0, p = m, t = x - 1; p; p --, t = x - i - 1)
    while (t)
    {
      while (i < n && t && !a[i]) i ++, t --;
      if (i < n && t)
      {
        if (a[i] >= t)
        {
          a[i] -= t, sum -= t;
  	      t = 0;
        }
        else
        {
          t -= a[i], sum -= a[i];
          a[i] = 0;
        }
      }
      if (sum == 0) return true;
    }
  return false;
}

lli binarySearch()
{
  lli lo = 0, hi = 1e16;
  while (lo < hi)
  {
    lli mid = (lo + hi) >> 1;
    if (can(mid)) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    sum = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      sum += a[i];
    }
    memcpy(aux, a, sizeof(a)), auxSum = sum;

    lli ans = binarySearch();
    printf("%lld\n", ans);
  }
  return 0;
}