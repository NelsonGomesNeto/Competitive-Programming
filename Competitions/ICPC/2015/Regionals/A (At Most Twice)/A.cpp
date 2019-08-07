#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli u, l;
lli base = 998877665544332211LL;
int cnt[10];

lli getNumber(vector<int> digits, int pos)
{
  lli number = 0; int c[10]; memcpy(c, cnt, sizeof(cnt));
  for (int i = pos; i < digits.size(); i ++)
    for (int d = 9; d >= 0; d --)
      if (c[d] < 2)
      {
        digits[i] = d, c[d] ++;
        break;
      }
  for (int d: digits) number = number*10 + d;
  return(number);
}
bool valid(lli number)
{
  int c[10]; memset(c, 0, sizeof(c));
  while (number)
  {
    c[number % 10] ++;
    if (c[number % 10] > 2) return(false);
    number /= 10;
  }
  return(true);
}

int main()
{
  while (scanf("%lld", &u) != EOF)
  {
    vector<int> digits; lli n = u; while (n) { digits.push_back(n % 10); n /= 10; }
    memset(cnt, 0, sizeof(cnt));
    reverse(digits.begin(), digits.end());
    lli ans = u * valid(u);
    for (int i = 0; i < digits.size(); i ++)
    {
      int prv = digits[i];
      for (int d = digits[i] - 1; d >= 0; d --)
        if (cnt[d] < 2)
        {
          digits[i] = d, cnt[d] ++;
          ans = max(ans, getNumber(digits, i + 1));
          cnt[d] --;
        }
      cnt[digits[i] = prv] ++;
      if (cnt[digits[i]] > 2) break;
    }
    printf("%lld\n", ans);
  }

  return(0);
}