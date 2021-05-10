#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, l, r;
map<int, int> lo, hi;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &n, &l, &r);

    lo.clear();
    for (int i = 0; i < l; i++)
    {
      int a; scanf("%d", &a);
      if (!lo.count(a)) lo[a] = 0;
      lo[a]++;
    }

    hi.clear();
    for (int i = 0; i < r; i++)
    {
      int a; scanf("%d", &a);
      if (!hi.count(a)) hi[a] = 0;
      hi[a]++;
    }

    int ans = 0;

    // Remove all matching pairs
    for (int k = 0; k < 2; k++)
    {
      list<int> loRemove, hiRemove;
      for (auto &[color, cnt]: lo)
        if (hi.count(color))
        {
          int matches = min(cnt, hi[color]);
          cnt -= matches, l -= matches;
          if (cnt == 0)
            loRemove.push_back(color);

          hi[color] -= matches, r -= matches;
          if (hi[color] == 0)
            hiRemove.push_back(color);
        }
      for (int i: loRemove) lo.erase(i);
      for (int i: hiRemove) hi.erase(i);

      swap(lo, hi), swap(l, r);
    }

    // Ensure l has the biggest amount of socks
    if (l < r) swap(lo, hi), swap(l, r);

    DEBUG printf("\t%d %d\n", l, r);

    // Turn l socks into r socks, if there's more then 2 of a color
    // This way we don't have to pay for recoloring
    int remaining = (l - r) >> 1;
    for (auto &[color, cnt]: lo)
      if (cnt >= 2 && remaining)
      {
        int canTurn = min(remaining, cnt >> 1);
        remaining -= canTurn, ans += canTurn;
        l -= 2*canTurn;
      }

    // Turn the remaining
    ans += (l - r) >> 1;

    // Paint the unmatches
    ans += (l + r) >> 1;

    printf("%d\n", ans);
  }
  return 0;
}
