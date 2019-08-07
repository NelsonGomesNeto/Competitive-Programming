#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
vector<pair<int, int> > graph[10000];
int cost[10000][601], trust[10000];
int n, inf = 16843009;

int dijkstra(int source, int target)
{
  for (int i = 0; i < n; i ++) cost[source][i] = 0;
  priority_queue<vector<int>, vector<vector<int> >, greater<vector<int> > > pq;
  pq.push({cost[source][0], 0, source});
  while (!pq.empty())
  {
    int t = pq.top()[1], v = pq.top()[2], c = pq.top()[0]; pq.pop();
    DEBUG printf("%d %d %d %d\n", v, t, c, trust[v]);
    for (auto u: graph[v])
    {
      DEBUG printf("%d connected to %d %d\n", v, u.first, u.second);
      if (u.second <= 600 && trust[v] && c + 1 < cost[u.first][u.second])
      {
        cost[u.first][u.second] = c + 1;
        pq.push({c + 1, u.second, u.first});
      }
      if (t + u.second <= 600 && c < cost[u.first][t + u.second])
      {
        cost[u.first][t + u.second] = c;
        pq.push({c, t + u.second, u.first});
      }
    }
  }
  int best = inf;
  for (int i = 0; i <= 600; i ++)
    best = min(best, cost[target][i]);
  if (best == inf) best = -1;
  return(best);
}

int hasPath(int u, int target, int visited[])
{
  if (u == target) return(1);
  if (visited[u]) return(0);
  visited[u] = 1;
  for (auto v: graph[u])
    if (hasPath(v.first, target, visited))
      return(1);
  return(0);
}

int main()
{
  while (scanf("%d", &n) && n)
  {
    int t; scanf("%d", &t);
    int k;
    memset(trust, 0, sizeof(trust));
    for (int i = 0; i < t; i ++)
    {
      scanf("%d", &k);
      trust[k] = 1;
    }
    int connections; scanf("%d", &connections);
    int u, v, c;
    for (int i = 0; i < n; i ++) graph[i].clear();
    while (connections --)
    {
      scanf("%d %d %d", &u, &v, &c); u --;  v --;
      graph[u].push_back({v, c});
      graph[v].push_back({u, c});
    }

    int visited[n]; memset(visited, 0, sizeof(visited));
    if (hasPath(0, n - 1, visited))
    {
      memset(cost, 1, sizeof(cost));
      int ans = dijkstra(0, n - 1);
      printf("%d\n", ans);
    }
    else printf("-1\n");
  }
  return(0);
}