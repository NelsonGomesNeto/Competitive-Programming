#include <bits/stdc++.h> #define lli long long int
using namespace std;

const int maxN = 1e5; int n, m, k, x, source, target;
vector<pair<int, int>> graph[maxN]; vector<int> chocolates;
lli costs[2][maxN], inf = 1e18;

void dijkstra(lli cost[], int s)
{
  for (int i = 0; i < n; i ++) cost[i] = inf;
  priority_queue<pair<lli, int>> pq; pq.push({0, s}); cost[s] = 0;
  while (!pq.empty())
  {
    int u = pq.top().second; pq.pop();
    for (auto v: graph[u])
      if (cost[u] + v.second < cost[v.first])
      {
        cost[v.first] = cost[u] + v.second;
        pq.push({-cost[v.first], v.first});
      }
  }
}

int main()
{
  scanf("%d %d %d %d", & n, & m, & k, & x);
  for (int i = 0, u; i < k; i ++)
  {
    scanf("%d", & u); u --;
    chocolates.push_back(u);
  }
  for (int i = 0; i < m; i ++)
  {
    int u, v, c; scanf("%d %d %d", & u, & v, & c); u --, v --;
    graph[u].push_back({v, c}); graph[v].push_back({u, c});
  }
  scanf("%d %d", & source, & target); source --, target --;
  dijkstra(costs[0], source); dijkstra(costs[1], target);

  lli ans = inf;
  for (int c: chocolates)
    if (costs[1][c] <= x)
      ans = min(ans, costs[0][c] + costs[1][c]);
  printf("%lld\n", ans == inf ? -1 : ans);

  return (0);
}
