#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli n, lli d)
{
  lli an = a1 + (n - 1)*d;
  return n * (a1 + an) >> 1;
}

const int maxN = 2e5;
int n;
int pos[maxN];
vector<int> p(maxN);
string ansString;

int main()
{
  int testCases;
  scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &p[i]);
      pos[p[i]] = i;
    }

    DEBUG {
      printf("p:");
      for (int i = 0; i < n; ++i) printf(" %d", p[i]);
      printf("\n");
    }

    lli ans = 0;
    int lo = pos[0], hi = pos[0];
    for (int i = 0; i < n; ++i)
    {
      lo = min(lo, pos[i]), hi = max(hi, pos[i]);
      int mex = i + 1;
      int sz = hi - lo + 1;

      // (sz - 1 + available) / 2 < mex
      // sz - 1 + available < 2*mex
      // available < 2*mex - sz + 1
      int available = 2*mex - sz;
      if (available < 0)
        continue;

      int nxtPos = i + 1 == n ? -100 : pos[i + 1];
      // To avoid overlaps: don't count the ones that include i + 1
      if (nxtPos >= lo && nxtPos <= hi)
        continue;

      DEBUG printf("\t%d | %d | %d %d\n", i, available, lo, hi);
      int j = available;
      int minDelta = min(j, lo);
      if (i != n - 1 && nxtPos < lo && lo - minDelta <= nxtPos)
        minDelta = min(minDelta, lo - nxtPos - 1);

      int maxDelta = min(j, n - hi - 1);
      if (i != n - 1 && nxtPos > hi && nxtPos <= hi + maxDelta)
        maxDelta = min(maxDelta, nxtPos - hi - 1);

      lli toAdd = 0;
      // x <= j - k
      // x <= minDelta

      // k + minDelta > j
      // k > j - minDelta

      lli below = min(maxDelta, j - minDelta);
      toAdd += (below + 1) * (minDelta + 1);

      // for (int k = below + 1; k <= maxDelta; ++k)
      //   toAdd += j - k + 1;
      toAdd += apSum(j - (below + 1) + 1, maxDelta - (below + 1) + 1, -1);

      ans += toAdd;
      DEBUG printf("\t\t%d %d %d - %d\n", minDelta, maxDelta, below, toAdd);
    }

    printf("%lld\n", ans);
  }

  return 0;
}
