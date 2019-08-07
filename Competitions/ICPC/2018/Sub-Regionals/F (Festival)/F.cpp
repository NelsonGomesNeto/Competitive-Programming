#include <bits/stdc++.h>
#define lli long long int
using namespace std;
int n;
vector<pair<vector<int>, int> > events;
lli dp[1001][1024];
int nextEvent[1000];
lli inf = 1<<30;

lli solve(int i, int done)
{
  if (i == events.size()) return(done == (1 << n) - 1 ? 0 : -inf);

  if (dp[i][done] == -1)
    dp[i][done] = max(solve(i + 1, done), events[i].first[2] + solve(nextEvent[i], done | (1 << events[i].second)));

  return(dp[i][done]);
}

int main()
{
  memset(dp, -1, sizeof(dp));

  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    int m, s, e, o; scanf("%d", &m);
    for (int j = 0; j < m; j ++)
    {
      scanf("%d %d %d", &s, &e, &o);
      events.push_back({{s, e, o}, i});
    }
  }
  sort(events.begin(), events.end());

  for (int i = 0; i < events.size(); i ++)
  {
    int j = i + 1;
    while (j < events.size() && events[i].first[1] > events[j].first[0]) j ++;
    nextEvent[i] = j;
  }

  lli ans = solve(0, 0);
  printf("%lld\n", ans < 0 ? -1 : ans);

  return(0);
}