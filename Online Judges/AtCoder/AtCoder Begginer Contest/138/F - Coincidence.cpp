#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
1: x <= y
target: y XOR x == y % x

2: y XOR x < x, since y % x < x

Let's look for the choices of MSB (Most Significant Bit) of x
Because of rule 1, MSB(x) <= MSB(y)
  MSB(x) < MSB(y):
    2^MSB(y) will *always* be 1 after y XOR x
    BUT, this means y XOR x > x, violating rule 2
  MSB(x) == MSB(y):
    Now 1 <= y / x < 2, so y % x == y - x

  Now, y XOR x = y - x and MSB(x) == MSB(y)
  That will happen always, as long as we don't have
  a 2^k where x & 2^k == 1 and y & 2^k == 0, all other
    x & 2^k == 0 and y & 2^k == 0 }
    x & 2^k == 0 and y & 2^k == 1 } are allowed
    x & 2^k == 1 and y & 2^k == 1 }
*/

const lli mod = 1e9 +7;
lli l, r;

const int maxB = 61;
lli memo[maxB][2][2][2][2];
lli solve(int i = maxB - 1, bool hadMsb = false, bool equalR = true, bool equalLy = true, bool equalLx = true, string y = "", string x = "")
{
  DEBUG printf("%d - %d - %d - %d %d || %s || %s\n", i, hadMsb, equalR, equalLy, equalLx, y.c_str(), x.c_str());
  if (i == -1) return 1;
  lli &ans = memo[i][hadMsb][equalR][equalLy][equalLx];
  if (ans != -1) return ans;

  ans = 0;
  if (hadMsb)
  {
    for (int by = equalLy ? (l >> i) & 1 : 0, end = equalR ? (r >> i) & 1 : 1; by <= end; by++)
      for (int bx = equalLx ? (l >> i) & 1 : 0; bx <= by; bx++)
        ans = (ans + solve(i - 1, true,
                           equalR & (by == ((r >> i) & 1)),
                           equalLy & (by == ((l >> i) & 1)),
                           equalLx & (bx == ((l >> i) & 1)),
                           y + to_string(by),
                           x + to_string(bx))
                           ) % mod;
  }
  else
  {
    for (int b = equalLy ? (l >> i) & 1 : 0, end = equalR ? (r >> i) & 1 : 1; b <= end; b++)
      ans = (ans + solve(i - 1, b,
                         equalR & (b == ((r >> i) & 1)),
                         equalLy & (b == ((l >> i) & 1)),
                         equalLx & (b == ((l >> i) & 1)),
                         y + to_string(b),
                         x + to_string(b))
                         ) % mod;
  }
  return ans;
}

int main()
{
  while (~scanf("%lld %lld", &l, &r))
  {
    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}