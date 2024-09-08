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
    char s[n + 1]; scanf(" %s", s);
    string ss = string(s), ta = "2020";

    bool can = false;
    if (ss.substr(0, 4) == ta)
      can = true;
    if (ss.substr(n - 4) == ta)
      can = true;

    for (int i = 1; i <= 3; i++)
    {
      if (ss.substr(0, i) == ta.substr(0, i) && ss.substr(n - (4 - i)) == ta.substr(i))
        can = true;
    }

    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
