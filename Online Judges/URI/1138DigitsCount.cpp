#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b;
int currDigit; lli currNumber;

lli memo[10][10][2][2];
lli solve(int i = 9, int prv = 0, bool valid = false, bool onLimit = true)
{
  if (i <= -1) return prv;
  if (memo[i][prv][valid][onLimit] != -1) return memo[i][prv][valid][onLimit];
  lli ans = 0;
  int currNumberDigit = (lli)(currNumber / pow(10, i)) % 10;
  for (int d = 0; d <= (onLimit ? currNumberDigit : 9); d++)
    ans += solve(i - 1, prv + ((valid || (d > 0)) && d == currDigit), valid || (d > 0), onLimit && (d == currNumberDigit));
  return memo[i][prv][valid][onLimit] = ans;
}

lli f(lli n)
{
  memset(memo, -1, sizeof(memo));
  currNumber = n;
  return solve(log10(n));
}

int main()
{
  while (scanf("%lld %lld", &a, &b) != EOF && !(a == 0 && b == 0))
    for (currDigit = 0; currDigit <= 9; currDigit++)
      printf("%lld%c", f(b) - f(a - 1), currDigit < 9 ? ' ' : '\n');
  return 0;
}