#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, inf = 1e7; int n;
lli a[maxN];
vector<lli> all[61];
set<pair<lli, lli>> visited;

int bfs(lli start)
{
  visited.clear();
  queue<pair<lli, pair<lli, int>>> q; q.push({start, {-1, 0}});
  while (!q.empty())
  {
    lli u = q.front().first, prv = q.front().second.first; int d = q.front().second.second; q.pop();
    if (d > 1 && u == start) return(d);
    if (visited.count({u, prv})) continue;
    visited.insert({u, prv});
    for (int j = 0; j <= 60; j ++)
      if ((1LL << j) & u)
        for (lli v: all[j])
          if (v != u && v != prv)
            q.push({v, {u, d + 1}});
  }
  return(inf);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i <= 60; i ++) all[i].clear();

    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      for (int j = 0; j <= 60; j ++)
        if ((1LL << j) & a[i])
          all[j].push_back(a[i]);
    }

    bool smallestCycle = false;
    for (int i = 0; i <= 60; i ++)
      if (all[i].size() > 2)
        smallestCycle = true;
    if (smallestCycle) printf("3\n");
    else
    {
      int ans = inf;
      for (int i = 0; i <= 60; i ++)
        for (lli j: all[i])
          ans = min(ans, bfs(j));
      printf("%d\n", ans == inf ? -1 : ans);
    }
  }

  return(0);
}