#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, c0, c1, h;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d %d", &n, &c0, &c1, &h);
    scanf(" %s", s);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      if (s[i] == '1')
        ans += min(c1, h + c0);
      else
        ans += min(c0, h + c1);
    }

    printf("%d\n", ans);
  }
  return 0;
}
