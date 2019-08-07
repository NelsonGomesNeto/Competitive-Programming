#include <bits/stdc++.h>
using namespace std;
struct point { int x, y; };
point points[101]; int n;
map<int, int> xs, ys;

const int maxVertices = 1e4;
int source = 0, target, level[maxVertices], ptr[maxVertices], inf = 1e9; queue<int> q;
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool insidePolygon(int x, int y)
{
  bool c = false;
  for (int i = 0; i < n; i ++)
  {
    int x1 = points[i].x, x2 = points[i + 1].x, y1 = points[i].y, y2 = points[i + 1].y;
    // if (y1 == y2 && y == y1 && x >= min(x1, x2) && x <= max(x1, x2)) return(true);
    // if (x1 == x2 && x == x1 && y >= min(y1, y2) && y <= max(y1, y2)) return(true);
    double h = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)), a = sqrt(pow(x - x1, 2) + pow(y - y1, 2)), b = sqrt(pow(x - x2, 2) + pow(y - y2, 2));
    if (a + b - h <= 1e-6) return(true);
    if ((y1 > y) != (y2 > y) && (x < (x2 - x1) * (double) (y - y1) / (y2 - y1) + x1))
      c = !c;
  }
  return(c);
}

bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (auto &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}

int dfs(int u, int flow)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[u] + 1 == level[e.to])
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
  while (scanf("%d", &n) && n)
  {
    for (int i = 0; i < n; i ++) scanf("%d %d", &points[i].x, &points[i].y);
    points[n] = points[0]; xs.clear(); ys.clear();
    for (int i = 0; i < n; i ++)
    {
      if (!xs.count(points[i].x)) xs[points[i].x] = xs.size();
      if (!ys.count(points[i].y)) ys[points[i].y] = ys.size();
    }
    target = xs.size() + ys.size() + 1;
    for (int i = 0; i < 1e4; i ++) graph[i].clear();

    for (auto yi: ys) addEdge(1 + xs.size() + yi.second, target, 1);
    for (auto xi: xs)
    {
      addEdge(source, 1 + xi.second, 1);
      for (auto yi: ys)
        if (!insidePolygon(xi.first, yi.first))
          addEdge(1 + xi.second, 1 + xs.size() + yi.second, 1);
    }
    printf("%d\n", (int) (xs.size() + ys.size() - dinic()));
  }
  return(0);
}
