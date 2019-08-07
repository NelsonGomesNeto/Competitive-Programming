#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e4, inf = 1e9; int n, m;
vector<pair<int, int>> graph[maxN];

int dist[maxN], color[maxN], prvPath[maxN], groupSize[maxN];
void mergeGroup(int end, int start, int size)
{
  groupSize[end] = size;
  for (int i = start; i != end; i = prvPath[i]) groupSize[i] = size;
}
void dfs(int u = 0, int prv = -1, int nowDist = 0)
{
  if (color[u] == 2) return;
  if (color[u] == 1) { mergeGroup(u, prv, nowDist - dist[u]); return; }
  color[u] = 1, prvPath[u] = prv, dist[u] = nowDist;
  for (auto v: graph[u])
    if (v.first != prv)
      dfs(v.first, u, nowDist + v.second);
  color[u] = 2;
  if (groupSize[u] == -1) mergeGroup(u, u, 0);
}

int dijkstra(int source, int size)
{
  for (int i = 0; i < n; i ++) dist[i] = inf;
  priority_queue<pair<int, int>> pq;
  pq.push({dist[source] = 0, source});
  int ans = inf;
  while (!pq.empty())
  {
    int u = pq.top().second, d = pq.top().first; pq.pop();
    if (groupSize[u] >= size) ans = min(ans, groupSize[u] + 2*d);
    if (d > dist[u]) continue;
    for (auto v: graph[u])
      if (dist[u] + v.second < dist[v.first])
        pq.push({dist[v.first] = dist[u] + v.second, v.first});
  }
  return(ans);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++) graph[i].clear();
    for (int i = 0, u, v, c; i < m; i ++)
    {
      scanf("%d %d %d", &u, &v, &c); u --, v --;
      graph[u].push_back({v, c}), graph[v].push_back({u, c});
    }
    memset(color, 0, sizeof(color)), memset(groupSize, -1, sizeof(groupSize));
    dfs();

    int q; scanf("%d", &q);
    while (q --)
    {
      int u, c; scanf("%d %d", &u, &c); u --;
      int d = dijkstra(u, c);
      printf("%d\n", d == inf ? -1 : d);
    }
  }

  return(0);
}