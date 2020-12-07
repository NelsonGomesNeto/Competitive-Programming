#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  a + b == a xor b <=> a & b == 0, where & is the bitwise-and operator.
  Now think about solving another problem:
    Count the pairs of numbers (a, b), where a <= l and b <= r and a & b == 0.
    Digit-DP is the way, but in binary instead of decimal (I will explain, wait)
  Suppose we had an f(l, r) that solved the problem above:
    ans = f(r, r) - 2*f(l - 1, r) + f(l - 1, l - 1)
      f(r, r) will count all pairs where a <= r and b <= r
        But will count: (a < l, b <= r) and (a <= r, b < l)
      f(l - 1, r) will count all pairs where a < l and b <= r
        But we need to multiply by two since there's also (a <= r, b < l) to be discarded
      f(l - 1, l - 1) will count all pairs where a < l and b < l
        Since 2*f(l - 1, r) would have removed such ^ pairs ^ TWICE
        So, we add them again
  Back to Digit-DP, how can we count?
    Remember that we're trying to count all pair of numbers (a, b) such that a <= l and b <= r
    There are 3 informations on each state:
      bi, current bit [0 to 30]
      matchedL, wheter all bi from 30 to bi are matching l bi [true or false]
      matchedR, wheter all bi from 30 to bi are matching r bi [true or false]
    From state[bi, matchedL, matchedR], you can set the bi-th bit of a and b to:
      0, 0 - always
      0, 1 - iff setting b's bit to one will not make the number greater than r
        How can we know if we won't make a number greater than r?
          if !matchedR or r's bi-th bit is 1
      1, 0 - iff setting a's bit to one will not make the number greater than l
        You can verify that using the same idea above
      1, 1 - never
    Remember to make the recursion from the leftmost bit to the rightmost bit (30 to 0),
    and also keep track of matchedL and matchedR
*/

const int BITS = 30;

lli memo[BITS + 1][2][2];
lli f(lli l, lli r, int bi = BITS, bool matchedL = true, bool matchedR = true)
{
  if (l < 0 || r < 0) return 0;
  if (bi == -1) return 1;

  if (memo[bi][matchedL][matchedR] == -1)
  {
    lli ans = 0;
    for (int i = 0; i < 2; i ++)
      for (int j = 0; i + j < 2; j ++)
      {
        // Preventing combinations that are greater than l and r
        if (matchedL && (l >> bi & 1) == 0 && i == 1) continue;
        if (matchedR && (r >> bi & 1) == 0 && j == 1) continue;
        ans += f(l, r, bi - 1, matchedL && (l >> bi & 1) == i, matchedR && (r >> bi & 1) == j);
      }
    memo[bi][matchedL][matchedR] = ans;
  }
  return memo[bi][matchedL][matchedR];
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli l, r; scanf("%lld %lld", &l, &r);
    memset(memo, -1, sizeof(memo));
    lli rr = f(r, r);
    memset(memo, -1, sizeof(memo));
    lli lr = f(l - 1, r);
    memset(memo, -1, sizeof(memo));
    lli ll = f(l - 1, l - 1);
    printf("%lld\n", rr - 2*lr + ll);
  }
  return 0;
}