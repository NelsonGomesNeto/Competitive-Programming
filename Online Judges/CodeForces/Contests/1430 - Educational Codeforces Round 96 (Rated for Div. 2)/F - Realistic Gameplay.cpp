#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n; lli k;
struct Wave
{
  lli l, r, a;
  lli size() { return r - l + 1; }
  void read() { scanf("%lld %lld %lld", &l, &r, &a); }
};
Wave waves[maxN];
vector<Wave> sepWaves;

lli solve(int i = 0, lli prvMonsters = 0)
{
  if (i == n) return 0;

  if (k >= prvMonsters )
  lli ans = solve(i + 1, 0);
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      waves[i].read();

    for (int i = 0; i < n; i++)
    {
      int j = i;
      while (j + 1 < n && waves[i].r == waves[j + 1].l) j++;
      if (i != j)
      {
        lli total = 0;
        for (int ii = i; ii < j; ii++)
          total += waves[ii].a;

        if (waves[i].l != waves[i].r)
        {
          lli remLo = waves[i].a / waves[i].size();
          sepWaves.push_back(Wave{waves[i].l, waves[i].r - 1, waves[i].a - remLo});
        }

        if (waves[j].l != waves[j].r)
        {
          lli remHi = waves[j].a / waves[j].size();
          total += remHi;
          sepWaves.push_back(Wave{waves[i].r, waves[i].r, total});
          sepWaves.push_back(Wave{waves[j].l + 1, waves[j].r, waves[j].a - remHi});
        }
        else
        {
          total += waves[j].a;
          sepWaves.push_back(Wave{waves[i].r, waves[i].r, total});
        }
      }
      else
        sepWaves.push_back(waves[i]);
    }

    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}