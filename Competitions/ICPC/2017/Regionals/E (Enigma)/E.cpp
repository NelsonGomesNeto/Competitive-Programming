#include <bits/stdc++.h>
using namespace std;
char s[(int) 1e3 + 1]; int n, sz, firstZero;
int dp[1000][1001];

/* Explanation:
First we need to be capable to calculate bigInteger % mod
We can do that by writing the bigInteger as powers of 10
  example: 343 == 3*10^2 + 4*10^1 + 3*10^0
And since: (x_1 % mod + x_2 % mod + ... + x_n % mod) % mod = (x_1 + x_2 + ... + x_n) % mod
x % mod can be: (sum (i from 0 to log10(x)) (digit(x, i) * 10^i % mod) ) % mod

Nice, with that said, we run a DP with a bidimensional memo
  first dimension: position in the string
  second dimension: actual remainder
  where memo[i][rem] answers: "can we build a number from this position having this remainder already"
Now we can try to build the number from left to right, always sending forward
the remainder we now have. If s[i] == '?' we just calculate the remainder and
go forward, else we try every possible digit (be careful with 0s on the left)

We always save the minimum, so that if we have a 0 at memo[0][0]: we can build

And the smallest number will actually be the first number, if we've tried from
left to right (the number) and from 0 to 9 (the digits); so you can forcelly break
whenever you've found the memo[i][rem] = 0
O(s*n)
*/

int modExp(int x, int y, int mod)
{
  if (!y) return(1);
  int ret = modExp(x, y >> 1, mod);
  ret = (ret * ret) % mod; if (y & 1) ret = (ret * x) % mod;
  return(ret);
}

int bigmod(char num, int p, int mod)
{
  return((num - '0') * modExp(10, p, mod));
}

int solve(int i, int rem)
{
  if (i == sz) return(rem);
  int p = sz - i - 1;
  if (dp[i][rem] == -1 || 1)
  {
    dp[i][rem] = n + 1;
    if (s[i] != '?')
      dp[i][rem] = solve(i + 1, (rem + bigmod(s[i], p, n)) % n);
    else
      for (int k = (i == 0 && firstZero); k <= 9; k ++)
      {
        s[i] = k + '0';
        dp[i][rem] = min(dp[i][rem], solve(i + 1, (rem + bigmod(s[i], p, n)) % n));
        if (dp[i][rem] == 0) break;
        s[i] = '?';
      }
  }
  return(dp[i][rem]);
}

int main()
{
  scanf("%s %d", s, &n); sz = strlen(s);
  firstZero = s[0] == '?';
  memset(dp, -1, sizeof(dp));
  solve(0, 0);
  if (dp[0][0]) printf("*\n");
  else printf("%s\n", s);
  return(0);
}
