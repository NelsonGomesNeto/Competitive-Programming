#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxM = 1000;
int c, d;
int x[maxN];
int ans[maxM], upt[maxN];
vector<pair<int, int>> graph[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &c, &d);
    for (int i = 1; i < c; i++)
      scanf("%d", &x[i]);
    for (int i = 0; i < d; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back({v, i}), graph[v].push_back({u, i});
    }

    memset(ans, -1, sizeof(ans));
    memset(upt, -1, sizeof(upt));
    int updated = 1, curr = 0;
    upt[0] = 0;
    while (updated < c)
    {
      int nowUpdated = updated;
      for (int i = 0; i < c; i++)
        if (-x[i] == nowUpdated)
        {
          int minTime = 1e9;
          for (auto &e: graph[i])
            if (upt[e.first] != -1)
              minTime = min(minTime, upt[e.first]);
          upt[i] = minTime + 1;

          for (auto &e: graph[i])
          {
            if (upt[e.first] != -1 && ans[e.second] == -1)
              ans[e.second] = upt[i] - upt[e.first];
            // if (ans[e.second] == -1)
              // ans[e.second] = upt[i] + 1;
          }
          updated++;
        }
      curr++;
    }

    printf("Case #%d:", tt);
    for (int i = 0; i < d; i++) printf(" %d", ans[i]);
    printf("\n");
  }
  return 0;
}