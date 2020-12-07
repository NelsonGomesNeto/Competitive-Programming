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
    int n, m; scanf("%d %d", &n, &m);
    set<int> bot;
    for (int i = 0; i < n; i++)
    {
      int b; scanf("%d", &b);
      bot.insert(b);
    }
    set<int> left;
    for (int i = 0; i < m; i++)
    {
      int l; scanf("%d", &l);
      left.insert(l);
    }

    int ans = 0;
    for (int b: bot)
      for (int l: left)
        if (b == l)
          ans++;
    printf("%d\n", ans);
  }
  return 0;
}