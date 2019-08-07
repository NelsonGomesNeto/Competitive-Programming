#include <bits/stdc++.h>
using namespace std;
int n, m, s;

int dijkstra(vector<pair<int, int> > graph[], int cost[])
{
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  cost[s] = 0;
  pq.push({cost[s], s});
  while (!pq.empty())
  {
    int c = pq.top().first, u = pq.top().second; pq.pop();
    //printf("%d %d\n", u, c);
    for (auto v: graph[u])
      if (c + v.second < cost[v.first])
      {
        cost[v.first] = c + v.second;
        pq.push({cost[v.first], v.first});
      }
  }
  int closest = 16843009, furthest = -16843009;
  for (int i = 0; i < n; i ++)
  {
    if (s == i) continue;
    closest = min(closest, cost[i]);
    furthest = max(furthest, cost[i]);
  }
  return(furthest - closest);
}

int main()
{
  scanf("%d %d", &n, &m);
  vector<pair<int, int> > graph[n]; int u, v, p;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &p); u --; v --;
    graph[u].push_back({v, p});
    graph[v].push_back({u, p});
  }
  scanf("%d", &s); s --;

  int cost[n]; memset(cost, 1, sizeof(cost));
  int cf = dijkstra(graph, cost);
  printf("%d\n", cf);

  return(0);
}
