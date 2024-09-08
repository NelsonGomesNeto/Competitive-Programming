#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli l, r;

vector<int> digits;
vector<int> getDigits(lli num)
{
  vector<int> d;
  while (num)
  {
    d.push_back(num % 10);
    num /= 10;
  }
  if (d.empty()) d.push_back(0);
  // reverse(d.begin(), d.end());
  return d;
}
lli memo[20][2][2];
lli solve(int i = digits.size() - 1, bool equal = true, bool started = false)
{
  if (i == -1) return 0;
  lli &ans = memo[i][equal][started];
  if (ans != -1) return ans;

  ans = 0;
  for (int d = equal ? digits[i] : 9; d >= 0; d--)
    ans += solve(i - 1,
                 equal & (digits[i] == d),
                 started || (d != 0))
          + (started || (d != 0));
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %lld", &l, &r);

    memset(memo, -1, sizeof(memo));
    digits = getDigits(r);
    lli rr = solve();
    memset(memo, -1, sizeof(memo));
    digits = getDigits(l);
    lli ll = solve();
    printf("%lld\n", rr - ll);
  }
  return 0;
}
