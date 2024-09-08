#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli asBase11(lli x)
{
  lli ans = 0, pot = 1;
  while (x)
  {
    ans += (x % 10) * pot;
    x /= 10, pot *= 11;
  }
  return ans;
}
const int maxN = 100; lli s; int n;
lli ans[maxN];

lli eval(int i, lli x)
{
  ans[i] = x;
  ans[n - 1] -= x - 1;
  lli res = 0;
  for (int j = 0; j < n; j++)
    res += asBase11(ans[j]);
  ans[n - 1] += x - 1;
  return res;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %d", &s, &n);
    for (int i = 0; i < n; i++) ans[i] = 0;

    lli budget = s;
    for (int i = 0; i < n; i++)
    {
      lli limit = budget - (n - i - 1);
      lli pot = 1;
      while (pot * 10 <= limit)
        pot *= 10;

      lli mult = 1;
      // while (mult < 9 && (mult + 1) * pot <= limit)
      //   mult++;

      ans[i] = pot * mult;
      budget -= ans[i];
    }
    ans[n - 1] += budget;

    for (int i = 0; i < n; i++)
      printf("%lld%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
