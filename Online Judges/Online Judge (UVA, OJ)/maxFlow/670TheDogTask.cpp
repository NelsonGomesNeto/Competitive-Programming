#include <bits/stdc++.h>
using namespace std;
struct point { int x, y; };
point master[100], interesting[100];

// source (0) -> master (1 : 99) -[if can be reached]> interesting (100 : 199) -> target (200)
const int maxVertices = 201, inf = 1e7;
int source = 0, target, vertices;
int level[maxVertices], ptr[maxVertices];
deque<int> q;
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

double distance(point a, point b)
{
  return(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0; q.push_back(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop_front();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push_back(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}

int dfs(int u, int flow)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[e.to] == level[u] + 1)
    {
      int delivered = dfs(e.to, min(e.flow, flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered);
    }
  }
  return(0);
}

int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs(source, inf)) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  int t, r = 0; scanf("%d", &t);
  while (t --)
  {
    if (r ++) printf("\n");
    int n, m; scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i ++)
      scanf("%d %d", &master[i].x, &master[i].y);
    for (int i = 0; i < m; i ++)
      scanf("%d %d", &interesting[i].x, &interesting[i].y);

    target = n + m; vertices = target + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();
    for (int i = 0; i < n - 1; i ++)
    {
      double distToNext = distance(master[i], master[i + 1]);
      addEdge(source, 1 + i, 1);
      for (int j = 0; j < m; j ++)
      {
        double toRun = distance(master[i], interesting[j]) + distance(interesting[j], master[i + 1]);
        if (toRun <= 2 * distToNext) addEdge(1 + i, n + j, 1);
      }
    }
    for (int j = 0; j < m; j ++) addEdge(n + j, target, 1);

    int maxFlow = dinic();
    int toVisit[n]; memset(toVisit, -1, sizeof(toVisit));
    for (Edge &e: graph[source])
      if (!e.flow)
      {
        for (Edge &ee: graph[e.to])
          if (!ee.flow)
          {
            toVisit[e.to - 1] = ee.to - n;
            break;
          }
      }

    printf("%d\n", maxFlow + n);
    for (int i = 0; i < n - 1; i ++)
    {
      if (i) printf(" ");
      printf("%d %d", master[i].x, master[i].y);
      if (toVisit[i] != -1) printf(" %d %d", interesting[toVisit[i]].x, interesting[toVisit[i]].y);
    }
    printf(" %d %d\n", master[n - 1].x, master[n - 1].y);
  }
  return(0);
}
