#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int w, h;
vector<int> horizontal[2]; int hbase[2];
vector<int> vertical[2]; int vbase[2];

lli calcInsideArea(lli lox, lli hix, lli x, lli height)
{
  return (x - lox) * height + (hix - x) * height;
}
lli calcOutsideArea(lli lox, lli hix, lli x, lli height)
{
  if (x <= lox) return (hix - x) * height - (lox - x) * height;
  else return (x - lox) * height - (x - hix) * height;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &w, &h);
    for (int i = 0; i < 2; i++)
    {
      horizontal[i].clear();
      int k; scanf("%d", &k);
      horizontal[i].resize(k);
      for (auto &x: horizontal[i]) scanf("%d", &x);
      hbase[i] = horizontal[i].back() - horizontal[i][0];
    }
    for (int i = 0; i < 2; i++)
    {
      vertical[i].clear();
      int k; scanf("%d", &k);
      vertical[i].resize(k);
      for (auto &y: vertical[i]) scanf("%d", &y);
      vbase[i] = horizontal[i].back() - horizontal[i][0];
    }

    lli ans = 0;
    for (int i = 0; i < 2; i++)
    {
      for (auto &x: horizontal[1 - i])
        if (x > horizontal[i][0] && x < horizontal[i].back())
        {
          ans = max(ans, calcInsideArea(horizontal[i][0], horizontal[i].back(), x, h));
        }
        else
        {
          ans = max(ans, calcOutsideArea(horizontal[i][0], horizontal[i].back(), x, h));
        }
    }
    for (int i = 0; i < 2; i++)
    {
      for (auto &x: vertical[1 - i])
        if (x >= vertical[i][0] && x <= vertical[i].back())
        {
          ans = max(ans, calcInsideArea(vertical[i][0], vertical[i].back(), x, w));
        }
        else
        {
          ans = max(ans, calcOutsideArea(vertical[i][0], vertical[i].back(), x, w));
        }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
