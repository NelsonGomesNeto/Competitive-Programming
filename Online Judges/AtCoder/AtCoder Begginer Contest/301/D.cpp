#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxBits = 60;
char ss[maxBits + 1];
string s;
lli n;

lli memo[maxBits][2];
lli solve(int i = s.size() - 1, bool isEqual = true, lli res = 0)
{
  DEBUG {
    for (int k = 0; k < s.size() - i; ++k) printf("\t");
    printf("%d %d %lld\n", i, isEqual, res);
  }

  if (res > n) return -1;
  if (i < 0) return res;
  lli& ans = memo[i][isEqual];
  if (ans != -2) return ans;

  ans = -1;
  if (s[i] == '?')
  {
    for (int b = isEqual ? ((n >> i) & 1LL) : 1; b >= 0; --b)
    {
      lli toAdd = b ? 1LL << i : 0;
      bool sameBit = ((n >> i) & 1LL) == b;
      ans = max(ans, solve(i - 1, isEqual & sameBit, res | toAdd));
    }
  }
  else
  {
    lli toAdd = s[i] == '1' ? 1LL << i : 0;
    bool sameBit = s[i] == '1' ? (n >> i) & 1LL : !((n >> i) & 1LL);
    ans = solve(i - 1, isEqual & sameBit, res | toAdd);
  }

  return ans;
}

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    scanf("%lld", &n);
    reverse(s.begin(), s.end());
    while (s.size() < maxBits) s.push_back('0');

    for (int i = 0; i < s.size(); ++i)
      for (int k = 0; k < 2; ++k)
        memo[i][k] = -2;

    lli ans = solve();
    printf("%lld\n", ans);
    DEBUG return 0;
  }
  return 0;
}
