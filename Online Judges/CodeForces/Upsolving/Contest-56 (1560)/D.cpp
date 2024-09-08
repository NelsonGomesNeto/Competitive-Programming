#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

vector<lli> powers;
vector<int> getDigits(lli num)
{
  if (!num) return {0};
  vector<int> ans;
  while (num)
  {
    ans.push_back(num % 10);
    num /= 10;
  }
  return ans;
}
lli dist(lli p, lli n)
{
  vector<int> pdigits = getDigits(p), ndigits = getDigits(n);
  int d = 0;
  int i = 0, j = 0;
  while (i < pdigits.size() && j < ndigits.size())
  {
    
  }
  return d;
}

int main()
{
  lli p = 1;
  while (p < 1e11)
  {
    powers.push_back(p);
    p *= 2LL;
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli n; scanf("%lld", &n);
    lli ans = 1e9;
    for (lli p: powers)
      ans = min(ans, dist(p, n));
    printf("%lld\n", ans);
  }
  return 0;
}
