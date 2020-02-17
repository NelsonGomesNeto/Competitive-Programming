#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
int a[maxN];
lli acc[maxN + 1];

int binarySearch(int l, lli x, int lo, int hi = n - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (acc[mid + 1] - acc[l] <= x) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);

    for (int i = 0; i < n; i ++)
      acc[i + 1] = acc[i] + a[i];

    int q; scanf("%d", &q);
    while (q --)
    {
      int l; lli x; scanf("%d %lld", &l, &x); l --;
      int r = binarySearch(l, x, l);
      printf("%d\n", x < a[l] ? -1 : r + 1);
    }
  }
  return 0;
}