#include <bits/stdc++.h>
#define lli long long int
using namespace std;

bool aa[7] = {true, false, false, true, false, false, true};
bool bb[7] = {false, true, false, false, false, true, false};
bool cc[7] = {false, false, true, false, true, false, false};

lli leftOver(lli left, int kind, int day)
{
  int totalDays = 0;
  while (left != -1)
  {
    left -= kind == 0 ? aa[day] : kind == 1 ? bb[day] : cc[day];
    day = (day + 1) % 7, totalDays ++;
  }
  return(totalDays - 1);
}

int main()
{
  lli a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
  lli ans = 0;
  for (int i = 0; i < 7; i ++)
  {
    lli today = min({a / 3 * 7 + leftOver(a % 3, 0, i), b / 2 * 7 + leftOver(b % 2, 1, i), c / 2 * 7 + leftOver(c % 2, 2, i)});
    ans = max(ans, today);
  }
  printf("%lld\n", ans);
  return(0);
}