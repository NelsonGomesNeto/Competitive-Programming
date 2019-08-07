#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e4, inf = 1e9; int n, m;
vector<pair<int, int>> graph[maxN];

int dist[maxN][2];
int dijkstra()
{
  for (int i = 0; i < n; i ++) dist[i][0] = dist[i][1] = inf;
  priority_queue<pair<int, pair<int, bool>>> pq; pq.push({0, {0, true}}); dist[0][1] = 0;
  while (!pq.empty())
  {
    int u = pq.top().second.first, d = -pq.top().first; bool even = pq.top().second.second; pq.pop();
    if (d > dist[u][even]) continue;
    for (auto v: graph[u])
      if (dist[u][even] + v.second < dist[v.first][!even])
      {
        dist[v.first][!even] = dist[u][even] + v.second;
        pq.push({-dist[v.first][!even], {v.first, !even}});
      }
  }
  return(dist[n - 1][1]);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v, c; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &c); u --, v --;
    graph[u].push_back({v, c}), graph[v].push_back({u, c});
  }

  int ans = dijkstra();
  printf("%d\n", ans == inf ? -1 : ans);

  return(0);
}