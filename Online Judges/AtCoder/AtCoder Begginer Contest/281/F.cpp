#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
const lli inf = 1LL << 50;
int n;
lli a[maxN];

lli solve(int bit = 30, int lo = 0, int hi = n - 1, lli x = 0)
{
  if (bit == -1)
  {
    // printf("\t%d | %d %d | %lld\n", bit, lo, hi, x);
    lli maximumValue = -1;
    for (int i = lo; i <= hi; ++i) maximumValue = max(maximumValue, a[i] ^ x);
    return maximumValue == -1 ? inf : maximumValue;
  }

  bool curr = (a[lo] >> bit) & 1;
  int failingI = -1;
  for (int i = lo; i <= hi; ++i)
    if (((a[i] >> bit) & 1) != curr)
    {
      failingI = i;
      break;
    }
  DEBUG {
    printf("%d | %d | %d %d | ", bit, failingI, lo, hi);
    for (int i = lo; i <= hi; ++i)
      printf("%d", ((a[i] >> bit) & 1));
    printf("\n");
  }
  if (failingI == -1)
  {
    if (curr == false)
      return solve(bit - 1, lo, hi, x);
    else
      return solve(bit - 1, lo, hi, x | (1LL << bit));
  }

  return min(solve(bit - 1, lo, failingI - 1, x | (1LL << bit)),
             solve(bit - 1, failingI, hi, x));
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      scanf("%lld", &a[i]);
    sort(a, a+n);
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
