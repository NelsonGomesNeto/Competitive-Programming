#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
lli monsters[maxN];
struct Hero
{
  lli p, s;
  void read() { scanf("%lld %lld", &p, &s); }
  bool operator<(const Hero &other) const
  {
    return p < other.p || (p == other.p && s < other.s);
  }
};
Hero heroes[maxN];

lli biggestEndurance[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    lli strongestMonster = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &monsters[i]);
      strongestMonster = max(strongestMonster, monsters[i]);
    }

    scanf("%d", &m);
    bool can = false;
    for (int i = 0; i < m; i ++)
    {
      heroes[i].read();
      biggestEndurance[i] = 0;
      if (heroes[i].p >= strongestMonster)
        can = true;
    }
    sort(heroes, heroes+m);
    biggestEndurance[m] = 0;
    for (int i = m - 1; i >= 0; i --)
      biggestEndurance[i] = max(biggestEndurance[i + 1], heroes[i].s);

    if (!can) printf("-1\n");
    else
    {
      int ans = 0, at = 0;
      while (at < n)
      {
        lli strongest = monsters[at];
        int jump = 0;
        while (at + jump < n)
        {
          strongest = max(strongest, monsters[at + jump]);
          int pos = lower_bound(heroes, heroes+m, Hero{strongest, 0}) - heroes;
          if (pos == m || heroes[pos].p < strongest || biggestEndurance[pos] <= jump)
            break;
          jump ++;
        }
        at += jump, ans ++;
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
