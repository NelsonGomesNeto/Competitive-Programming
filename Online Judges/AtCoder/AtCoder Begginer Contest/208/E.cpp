#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxDigits = 20;
lli n, k;
vector<int> digits;
unordered_map<lli, lli> memo[maxDigits][2][2];
lli solve(int i = 0, bool equal = true, bool started = false, lli prod = 1)
{
  if (i == digits.size()) return prod <= k && started;
  if (memo[i][equal][started].count(prod)) return memo[i][equal][started][prod];

  lli &ans = memo[i][equal][started][prod];
  ans = 0;
  for (int d = 0; d <= (equal ? digits[i] : 9); d++)
    ans += solve(i + 1, equal & (d == digits[i]), started | (d != 0), prod * (started | (d != 0) ? d : 1));
  return ans;
}

int main()
{
  while (~scanf("%lld %lld", &n, &k))
  {
    digits.clear();
    lli aux = n;
    while (aux)
    {
      digits.push_back(aux % 10);
      aux /= 10;
    }
    reverse(digits.begin(), digits.end());

    for (int i = 0; i < digits.size(); i++)
      memo[i][0][0].clear(), memo[i][0][1].clear(), memo[i][1][0].clear(), memo[i][1][1].clear();

    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}