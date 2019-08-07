#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e4; lli inf = 1e18; int n, m, source = 0, target;
struct State
{
  lli cost, t; int u;
  bool operator<(const State &b) const { return(cost < b.cost); }
};
vector<pair<int, lli>> graph[maxN];

lli dijkstra()
{
  lli cost[n][2]; for (int i = 0; i < n; i ++) cost[i][0] = cost[i][1] = inf;
  priority_queue<State> pq; pq.push({0, 0, source}); cost[source][0] = 0;
  while (!pq.empty())
  {
    int u = pq.top().u, t = pq.top().t; pq.pop();
    for (auto v: graph[u])
      if (cost[u][t] + v.second < cost[v.first][!t])
      {
        cost[v.first][!t] = cost[u][t] + v.second;
        pq.push({-cost[v.first][!t], !t, v.first});
      }
  }
  return(cost[target][0]);
}

int main()
{
  scanf("%d %d", &n, &m); target = n - 1;
  for (int i = 0; i < m; i ++)
  {
    int u, v; lli c; scanf("%d %d %lld", &u, &v, &c); u --, v --;
    graph[u].push_back({v, c}); graph[v].push_back({u, c});
  }
  lli ans = dijkstra();
  printf("%lld\n", ans >= inf ? -1 : ans);
  return(0);
}