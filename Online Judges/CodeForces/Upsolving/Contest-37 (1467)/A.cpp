#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    string ans = "";
    for (int i = 0, d = 9; i < n; i++)
    {
      if (i == 2) d = 9;
      ans += to_string(i == 1 ? 8 : d);
      d++;
      if (d > 9) d = 0;
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}
