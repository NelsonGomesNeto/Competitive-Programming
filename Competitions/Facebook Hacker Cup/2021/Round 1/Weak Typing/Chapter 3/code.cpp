#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8e5; int n;
const lli mod = 1e9 + 7;
char s[maxN + 1];
lli fullSize;
lli lSum, rSum, matches;

lli calc(lli l, lli r)
{
  r = (fullSize - r + 1 + mod) % mod;
  DEBUG printf("\t%lld %lld - %lld\n", l, r, fullSize);
  lSum = (lSum + l) % mod,
  rSum = (rSum + r) % mod,
  matches = (matches + 1) % mod;
  return l * r % mod;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", s);

    fullSize = lSum = rSum = matches = 0;
    for (int i = 0; i < n; i++)
    {
      if (s[i] != '.') fullSize = (fullSize + 1) % mod;
      else fullSize = fullSize * 2 % mod;
    }

    /*
      For each pair XO or OX: we can calculate the amount of substrings that will contain them
    */
    lli ans = 0;
    lli currSize = 0;
    lli firstX = -1, firstO = -1;
    lli lastX = -1, lastO = -1;
    lli prvAdd = 0;
    for (int i = 0; i < n; i++)
    {
      if (s[i] != '.') currSize = (currSize + 1) % mod;
      else
      {
        /* a*b
          (a + x) * (b - x) = a*b - a*x + b*x - x*x

          a*b + c*d -> (a + x) * (b - x) + (c + x) * (d - x)
                       (a*b + c*d) + ((b + d)*x - (a + c)*x) - 2*x^2
          a*b + c*d + e*f -> (a*b + c*d + e*f) + ((b + d + f)*x - (a + c + e)*x) - 3*x^2
        */
        lli toAdd = (ans
                    + (rSum - lSum + mod) % mod * currSize % mod
                    - matches * currSize % mod * currSize % mod
                    + mod) % mod;
        ans = (ans + toAdd) % mod;
        lSum = (lSum * 2 % mod + matches * currSize % mod) % mod,
        rSum = (rSum * 2 % mod - matches * currSize % mod + mod) % mod;
        matches = matches * 2 % mod;

        if (lastX != -1)
        {
          if (firstO != -1) ans = (ans + calc(lastX, (firstO + currSize) % mod)) % mod;
          lastX = (lastX + currSize) % mod;
        }
        if (lastO != -1)
        {
          if (firstX != -1) ans = (ans + calc(lastO, (firstX + currSize) % mod)) % mod;
          lastO = (lastO + currSize) % mod;
        }
        currSize = currSize * 2 % mod;
      }

      if (s[i] == 'O')
      {
        if (firstO == -1 && firstX == -1) firstO = currSize;
        lastO = currSize;
        if (lastX != -1)
        {
          ans = (ans + calc(lastX, lastO)) % mod;
          lastX = -1;
        }
      }
      if (s[i] == 'X')
      {
        if (firstX == -1 && firstO == -1) firstX = currSize;
        lastX = currSize;
        if (lastO != -1)
        {
          ans = (ans + calc(lastO, lastX)) % mod;
          lastO = -1;
        }
      }
    }

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}