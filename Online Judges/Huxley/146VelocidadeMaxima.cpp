#include <bits/stdc++.h>
using namespace std;

const int maxN = 500, inf = 1<<20; int n, source, target, m;
vector<int> graph[maxN][2]; int cost[maxN][3];

int dijkstra()
{
  for (int i = 0; i < n; i ++) cost[i][0] = cost[i][1] = cost[i][2] = inf;
  priority_queue<pair<int, int>> pq; pq.push({0, source}); cost[source][0] = 0;
  while (!pq.empty())
  {
    int u = pq.top().second, t = -pq.top().first; pq.pop();
    int opened = (t % 3) == 0;
    for (int v: graph[u][opened])
      if (cost[u][t % 3] + 1 < cost[v][(t + 1) % 3])
      {
        cost[v][(t + 1) % 3] = cost[u][t % 3] + 1;
        pq.push({-cost[v][(t + 1) % 3], v});
      }
  }
  return(min(cost[target][0], min(cost[target][1], cost[target][2])));
}

int main()
{
  scanf("%d %d %d %d", &n, &source, &target, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v, t; scanf("%d %d %d", &u, &v, &t);
    graph[u][t].push_back(v);
  }
  int ans = dijkstra();
  if (ans >= inf) printf("*\n");
  else printf("%d\n", ans);
  return(0);
}