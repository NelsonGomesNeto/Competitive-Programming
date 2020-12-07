#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  We will use Meet In The Middle here
  [countOnes(x ^ a_i) for i in [0 : n - 1]]
  Above is the resulting array, right?
  We could have tested for all numbers [0 : 2^30)
  But it's took costful

  Why not do it for all numbers [0 : 2^15) (first 15 bits (from right to left))
  For each one of them, we want to know if there's a corresponding number (with the last 15 bits)
  such that the array(a) + array(b) results in an array where all numbers are the same

  We use normalization for that:
    Normalization is to apply: a[i] -= a[0] for all i > 0; and then a[0] = 0
    Suppose you have the following array: norm([2, 3, 1, 4]) = [0, -1, 1, -2]
    Suppose you have the following array: norm([3, 2, 4, 1]) = [0, 1, -1, 2]
    Notice that both of them will give us the answer we want and the are exactly
    the opposite of each other.

  So we map all normalized array to it's number (with the first 15 bits)
  Then we test all numbers with the last 15 bits, normalize and flip (multiply by -1) the array
  If there's such an entry in our map: we reconstruct the number and DONE ^~^

  Observation: since we're looking only 15 bits, also restrict the
  countOnes to only those 15 bits
*/

const int maxN = 100, maxX = 1 << 15; int n;
lli a[maxN];
map<vector<int>, lli> low;

int ones(lli num)
{
  int o = 0;
  while (num)
  {
    o += num & 1LL;
    num >>= 1LL;
  }
  return o;
}

vector<int> eval(lli x, bool lowBits)
{
  vector<int> ans(n);
  for (int i = 0; i < n; i ++)
  {
    ans[i] = ones(a[i] ^ x) - (lowBits ? ones(a[i] & ~((1LL << 15LL) - 1LL)) : ones(a[i] & ((1LL << 15LL) - 1LL)));
    if (i) ans[i] -= ans[0]; // normalize
    if (i && lowBits) ans[i] *= -1LL;
  }
  ans[0] = 0;
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    low.clear();
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);

    lli ans = -1;
    for (lli bitmask = 0; bitmask < maxX; bitmask ++)
      low[eval(bitmask, true)] = bitmask;
    DEBUG {
      for (auto b: low)
      {
        printf("%lld:", b.second);
        for (int bb: b.first) printf(" %d", bb);
        printf("\n");
      }
    }
    for (lli bitmask = 0; bitmask < maxX && ans == -1; bitmask ++)
    {
      vector<int> b = eval(bitmask << 15LL, false);
      if (low.count(b))
        ans = low[b] + (bitmask << 15LL);
    }

    printf("%lld\n", ans);
  }
  return 0;
}
