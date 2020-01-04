#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  vector<string> days = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
  string today;
  cin >> today;

  int pos = 0;
  while (today != days[pos]) pos ++;

  int ans = 1;
  while (days[(pos + ans) % days.size()] != "SUN") ans ++;
  printf("%d\n", ans);

  return 0;
}