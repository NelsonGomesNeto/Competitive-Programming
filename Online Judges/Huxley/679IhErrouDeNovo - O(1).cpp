#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli n, lli d)
{
  lli an = a1 + (n - 1)*d;
  return n * (a1 + an) >> 1LL;
}

int main()
{
  int testCases;
  scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    lli k, a, b, c, d;
    scanf("%lld %lld %lld %lld %lld", &k, &a, &b, &c, &d);
    // if (a < 0)
    // {
    //   lli fixA = -a;
    //   a += fixA;
    //   b += fixA;
    //   k += fixA;
    // }
    lli sizeX = b - a + 1;
    lli sizeY = d - c + 1;

    // a <= x <= b
    // c <= y <= d
    // x + y > k
    lli ans = 0;
    lli missing = k - a - c + 1;
    DEBUG printf("\t%lld\n", missing);
    if (missing <= 0)
      ans = sizeX * sizeY;
    else
    {
      // missing = k - minX - minY + 1
      // such that minX + minY + missing > k
      // missing = k - a - c + 1
      // x + missing + anyY > k
      // x >= a + missing
      lli xBiggerThanMissing = max(0LL, b - (a + missing) + 1);
      DEBUG printf("\t%lld %lld\n", xBiggerThanMissing, sizeY);
      ans += xBiggerThanMissing * sizeY;

      // x < a + missing
      // require y to increase by k - x - c
      lli xSmallerThanMissing = max(0LL, sizeX - xBiggerThanMissing);
      lli minimumY = max(c, k - (a + xSmallerThanMissing - 1) + 1);
      lli sizeYfromMinimumY = d - minimumY + 1;
      DEBUG printf("\t%lld %lld %lld\n", xSmallerThanMissing, minimumY, sizeYfromMinimumY);
      if (sizeYfromMinimumY >= 0)
        ans += apSum(sizeYfromMinimumY, min(sizeYfromMinimumY, xSmallerThanMissing), -1);
    }

    printf("%lld\n", ans);
  }

  return 0;
}
