#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli l, r, cnt[19][10];

lli getDigits(lli num)
{
  lli digits = num == 0;
  while (num) num /= 10, digits ++;
  return digits;
}
lli pot(lli x, lli y)
{
  lli res = 1;
  while (y)
  {
    if (y & 1LL) res *= x;
    x *= x, y >>= 1LL;
  }
  return res;
}

lli getAns(lli num)
{
  if (num <= 1) return num;
  lli f = getDigits(num) - 1, c = getDigits(num);
  lli ans = 0, front = num / pot(10, f);
  for (int i = 1; i <= c; i ++)
  {
    DEBUG if (1 < front || i < c) printf("\t%d %lld -- %lld %lld %lld\n", i, num, f, c, front);
    for (int j = 1; j < front || (i < c && j <= 9); j ++)
      ans += cnt[i][j];
  }
  DEBUG printf("\t-- %lld %lld %lld\n", num, front*pot(10, f), (num - front*pot(10, f)) / 10 + (front <= num % 10));
  ans += (num - front*pot(10, f)) / 10 + (front <= num % 10);
  DEBUG printf("\t%lld\n", ans);
  return ans;
}

int main()
{
  for (int i = 1; i <= 18; i ++)
    for (int j = 1; j <= 9; j ++)
    {
      cnt[i][j] = pot(10, max(i - 2, 0));
      // printf("%d %d - %lld\n", i, j, cnt[i][j]);
    }

  while (scanf("%lld %lld", &l, &r) != EOF)
  {
    DEBUG printf("query: %lld %lld\n", l, r);
    lli lans = getAns(l - 1), rans = getAns(r);
    printf("%lld\n", rans - lans);
  }

  return 0;
}