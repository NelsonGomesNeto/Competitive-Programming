#include <bits/stdc++.h>
using namespace std;
int inf = 1e9, n, m;

pair<int, int> dijkstra(vector<pair<int, pair<int, int>>> graph[], int source, int target)
{
  int cost[n][2]; for (int i = 0; i < n; i ++) for (int j = 0; j < 2; j ++) cost[i][j] = inf;
  priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> pq;
  cost[source][0] = cost[source][1] = 0; pq.push({{0, 0}, source});
  while (!pq.empty())
  {
    int u = pq.top().second, walk = pq.top().first.first, total = pq.top().first.second; pq.pop();
    for (auto vv: graph[u])
    {
      int v = vv.first, c = vv.second.first, k = vv.second.second;
      if (k == 1 && (cost[u][0] + c < cost[v][0] || (cost[u][0] + c <= cost[v][0] && cost[u][1] + c < cost[v][1])))
      {
        cost[v][0] = cost[u][0] + c, cost[v][1] = cost[u][1] + c;
        pq.push({{cost[v][0], cost[v][1]}, v});
      }
      if (k == 2 && (cost[u][0] < cost[v][0] || (cost[u][0] <= cost[v][0] && cost[u][1] + c < cost[v][1])))
      {
        cost[v][0] = cost[u][0], cost[v][1] = cost[u][1] + c;
        pq.push({{cost[v][0], cost[v][1]}, v});
      }
    }
  }
  return(make_pair(cost[target][0], cost[target][1]));
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &n, &m);
    vector<pair<int, pair<int, int>>> graph[n]; int u, v, c, k;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d %d %d %d", &u, &v, &c, &k); u --, v --;
      graph[u].push_back({v, {c, k}});
      graph[v].push_back({u, {c, k}});
    }
    scanf("%d %d", &u, &v); u --, v --;
    pair<int, int> cost = dijkstra(graph, u, v);
    if (cost.first == inf || cost.second == inf) printf("-1\n");
    else printf("%d %d\n", cost.first, cost.second);
  }
  return(0);
}
