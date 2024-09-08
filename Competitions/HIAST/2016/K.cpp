#include <bits/stdc++.h>
using namespace std;
// source (0) -> soldiers (1 - n) -> places(n+1 - n+m) - target (n+1+m)
const int maxVertices = 100 + 1 + 100 + 1; int source = 0, target;
int level[maxVertices], inf = 1<<20;
struct Edge
{
  int to, back, flow, capacity;
};
vector<Edge> graph[maxVertices];

void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

int bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0;
  deque<int> q; q.push_back(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop_front();
    for (auto e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push_back(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}

int dfs(int u, int flow)
{
  if (u == target) return(flow);
  int totalDelivered = 0;
  for (auto &e: graph[u])
    if (e.flow && level[u] == level[e.to] - 1)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
      flow -= delivered;
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      totalDelivered += delivered;
    }
  return(totalDelivered);
}

int dinic()
{
  int maxFlow = 0, flow;
  while (bfs()) while (flow = dfs(source, inf)) maxFlow += flow;
  return(maxFlow);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, m, w; scanf("%d %d %d", &n, &m, &w); target = n+1+m;
    for (int i = 0; i <= target; i ++) graph[i].clear();

    vector<int> preferedPlaces[n];
    for (int i = 0; i < n; i ++)
    {
      int a, b; scanf("%d", &a);
      while (a --)
      {
        scanf("%d", &b); b --;
        preferedPlaces[i].push_back(b);
      }
    }

    vector<int> preferedWeapons[n];
    for (int i = 0; i < n; i ++)
    {
      int a, b; scanf("%d", &a);
      while (a --)
      {
        scanf("%d", &b);
        preferedWeapons[i].push_back(b);
      }
    }

    set<int> placeWeapons[m];
    for (int i = 0; i < m; i ++)
    {
      int a, b; scanf("%d", &a);
      while (a --)
      {
        scanf("%d", &b);
        placeWeapons[i].insert(b);
      }
    }

    for (int i = 0; i < n; i ++) addEdge(0, i + 1, 1);
    for (int i = 0; i < m; i ++) addEdge(n+1+i, target, 1);
    for (int i = 0; i < n; i ++)
      for (auto p: preferedPlaces[i])
        for (auto w: preferedWeapons[i])
          if (placeWeapons[p].count(w))
            addEdge(i + 1, n+1+p, 1);

    int maxFlow = dinic();
    printf("%d\n", maxFlow);
  }
  return(0);
}
