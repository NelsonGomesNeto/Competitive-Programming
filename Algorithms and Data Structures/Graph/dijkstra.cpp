#include <bits/stdc++.h>
using namespace std;
const int maxVertices = 1e3, inf = 1e9;
vector<pair<int, int>> graph[maxVertices];
int cost[maxVertices], prv[maxVertices];

int dijkstra(int source, int target)
{
  for (int i = 0; i < maxVertices; i ++) cost[i] = inf;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  cost[source] = 0; pq.push({cost[source], source});
  while (!pq.empty())
  {
    int u = pq.top().second; pq.pop();
    for (auto v: graph[u])
      if (cost[u] + v.second < cost[v.first])
      {
        cost[v.first] = cost[u] + v.second, prv[v.first] = u;
        pq.push({cost[v.first], v.first});
      }
  }
  return(cost[target]);
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int u, v, c;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &c); u --, v --;
    graph[u].push_back({v, c});
    graph[v].push_back({u, c});
  }
  printf("%d\n", dijkstra(0, n - 1));
  for (int i = 0; i < n; i ++) printf("%3d%c", i, i < n - 1 ? ' ' : '\n');
  for (int i = 0; i < n; i ++) printf("%3d%c", prv[i], i < n - 1 ? ' ' : '\n');
  return(0);
}
