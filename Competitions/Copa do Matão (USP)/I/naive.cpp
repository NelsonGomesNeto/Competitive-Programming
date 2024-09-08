#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
lli a[maxN];

lli getSum(int lo, int hi, lli x)
{
  lo--, hi--;
  lli sum = 0;
  for (int i = lo; i <= hi; i++)
    if (a[i] <= x)
      sum += a[i];
  return sum;
}

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    lli prvAns = 0;
    for (int qq = 0; qq < q; qq++)
    {
      int x, y; lli z; scanf("%d %d %lld", &x, &y, &z);
      int l = 1 + (x + prvAns - 1) % n;
      int r = 1 + (y + prvAns - 1) % n;
      lli d = z + prvAns;

      lli bestSum = 0;
      for (int i = l - 1; i <= r - 1; i++)
      {
        lli sum = getSum(l, r, a[i]);
        if (sum <= d)
          bestSum = max(bestSum, sum);
      }

      lli ans = bestSum;
      printf("%lld\n", ans);
      prvAns = ans;
    }
  }
  return 0;
}