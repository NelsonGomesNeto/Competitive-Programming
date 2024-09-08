#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxK = 3e5, maxX = 1e6; int n, m, k;
lli vertical[maxN], horizontal[maxN];
int vmap[maxX + 1], hmap[maxX + 1];
lli closestVcnt[maxN], closestHcnt[maxN];

struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
};
Point people[maxK];

lli totalv, totalh;
map<lli, lli> cntvh[maxN], cnthv[maxN];

int main()
{
  memset(vmap, -1, sizeof(vmap));
  memset(hmap, -1, sizeof(hmap));

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++)
    {
      cntvh[i].clear();
      closestVcnt[i] = 0;
      scanf("%lld", &vertical[i]);
      vmap[vertical[i]] = i;
    }
    for (int i = 0; i < m; i++)
    {
      cnthv[i].clear();
      closestHcnt[i] = 0;
      scanf("%lld", &horizontal[i]);
      hmap[horizontal[i]] = i;
    }

    totalv = totalh = 0;
    lli ans = 0;
    for (int i = 0; i < k; i++)
    {
      people[i].read();
      if (vmap[people[i].x] != -1 && hmap[people[i].y] != -1)
        continue;

      if (vmap[people[i].x] != -1)
      {
        int closestH = lower_bound(horizontal, horizontal+m, people[i].y) - horizontal;
        ans += closestHcnt[closestH] - cnthv[closestH][vmap[people[i].x]];
        closestHcnt[closestH]++;
        cnthv[closestH][vmap[people[i].x]]++;
      }
      if (hmap[people[i].y] != -1)
      {
        int closestV = lower_bound(vertical, vertical+n, people[i].x) - vertical;
        ans += closestVcnt[closestV] - cntvh[closestV][hmap[people[i].y]];
        closestVcnt[closestV]++;
        cntvh[closestV][hmap[people[i].y]]++;
      }
    }

    // for (int i = 0; i < k; i++)
    // {
    //   if (vmap[people[i].x] != -1 && hmap[people[i].y] != -1)
    //     continue;

    //   if (vmap[people[i].x] != -1)
    //   {
    //     int closestH = lower_bound(horizontal, horizontal+m, people[i].y) - horizontal;
    //     ans += closestHcnt[closestH] - cntv[vmap[people[i].x]];
    //   }
    //   if (hmap[people[i].y] != -1)
    //   {
    //     int closestV = lower_bound(vertical, vertical+n, people[i].x) - vertical;
    //     ans += closestVcnt[closestV] - cnth[hmap[people[i].y]];
    //   }
    // }
    printf("%lld\n", ans);

    for (int i = 0; i < n; i++)
      vmap[vertical[i]] = -1;
    for (int i = 0; i < m; i++)
      hmap[horizontal[i]] = -1;
  }
  return 0;
}
