#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
int n, q;
lli a[maxN];

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d %d", &n, &q);
    lli evenCount = 0, oddCount = 0;
    lli evenSum = 0, oddSum = 0;
    for (int i = 0; i < n; ++i)
    {
      scanf("%lld", &a[i]);
      if (a[i] & 1)
        ++oddCount, oddSum += a[i];
      else
        ++evenCount, evenSum += a[i];
    }

    for (int i = 0; i < q; ++i)
    {
      int t; lli x; scanf("%d %lld", &t, &x);
      if (t == 0) // add to even
      {
        evenSum += evenCount * x;
        if (x & 1)
        {
          oddCount += evenCount;
          evenCount = 0;
        }
      }
      else
      {
        oddSum += oddCount * x;
        if (x & 1)
        {
          evenCount += oddCount;
          oddCount = 0;
        }
      }
      printf("%lld\n", evenSum + oddSum);
    }
  }

  return 0;
}
