#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxP = 1e6;
lli memo[maxP];

int binarySearch(lli target, int lo = 0, int hi = maxP - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (target >= memo[mid]) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  memo[0] = 1e9;
  memo[1] = 2;
  for (int i = 2; i < maxP; i++)
    memo[i] = memo[i - 1] + 3LL * i - 1;

  int t; scanf("%d", &t);
  while (t--)
  {
    lli n; scanf("%lld", &n);
    int res = 0;
    while (n > 0)
    {
      lli toRemove = memo[binarySearch(n)];
      if (toRemove > n) break;
      n -= toRemove, res++;
    }
    printf("%d\n", res);
  }
  return 0;
}
