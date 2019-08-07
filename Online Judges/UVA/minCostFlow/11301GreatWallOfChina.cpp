#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
// it's never going to be necessary to go to the left
char field[5][1001];

// source (0) -> field (1 : 2 * 5 * 1000) -> target (2*5*1000 + 1)
// but source will only be conected to alfalfas
// since cost is on the vertices, we're gonna need to duplicate vertices
const int maxVertices = 1 + 2*5*1000 + 1;
int source = 0, target, vertices, inf = 1e7;
int prevVertex[maxVertices], prevEdge[maxVertices], minFlow[maxVertices], cost[maxVertices], inqueue[maxVertices], potentials[maxVertices], visited[maxVertices];
struct Edge { int to, back, flow, capacity, cost; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f, int c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, -c});
}

bool SPFA()
{
  memset(inqueue, 0, sizeof(inqueue));
  for (int i = 0; i < vertices; i ++) cost[i] = minFlow[i] = inf;
  deque<int> q; q.push_back(source); cost[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop_front(); inqueue[u] = 0;
    for (int j = 0; j < graph[u].size(); j ++)
    {
      Edge &e = graph[u][j]; int newCost = cost[u] + e.cost;
      if (e.flow && newCost < cost[e.to])
      {
        if (!inqueue[e.to]) inqueue[e.to] = 1, q.push_back(e.to);
        cost[e.to] = newCost;
        minFlow[e.to] = min(minFlow[u], e.flow);
        prevVertex[e.to] = u, prevEdge[e.to] = j;
      }
    }
  }
  return(cost[target] != inf);
}

bool dijkstraWithPotentials()
{
  memset(visited, 0, sizeof(visited));
  for (int i = 0; i < vertices; i ++) cost[i] = minFlow[i] = inf;
  priority_queue<pair<int, int>> q;
  cost[source] = 0; q.push({cost[source], source});
  while (!q.empty())
  {
    int u = q.top().second; q.pop();
    if (visited[u]) continue;
    visited[u] = 1;
    for (int j = 0; j < graph[u].size(); j ++)
    {
      Edge &e = graph[u][j]; int newCost = cost[u] + e.cost + potentials[u] - potentials[e.to];
      if (e.flow && newCost < cost[e.to])
      {
        cost[e.to] = newCost;
        minFlow[e.to] = min(minFlow[u], e.flow);
        prevVertex[e.to] = u, prevEdge[e.to] = j;
        q.push({-cost[e.to], e.to});
      }
    }
  }
  for (int i = 0; i < vertices; i ++) potentials[i] += cost[i];
  return(cost[target] != inf);
}

bool bellmanFord()
{
  for (int i = 0; i < vertices; i ++) cost[i] = minFlow[i] = inf;
  cost[source] = 0;
  for (int i = 0, done = 0; i < vertices - 1; i ++, done = 0)
  {
    for (int u = 0; u < vertices; u ++)
      for (int j = 0; j < graph[u].size(); j ++)
      {
        Edge &e = graph[u][j];
        if (e.flow && cost[u] + e.cost < cost[e.to])
        {
          cost[e.to] = cost[u] + e.cost;
          minFlow[e.to] = min(minFlow[u], e.flow);
          prevVertex[e.to] = u, prevEdge[e.to] = j;
          done = 1;
        }
      }
    if (!done) break;
  }
  return(cost[target] != inf);
}

pair<int, int> minCostFlow()
{
  memset(potentials, 0, sizeof(potentials));
  int minCost = 0, totalFlow = 0;
  while (SPFA())
  {
    int flow = minFlow[target];
    totalFlow += flow;
    for (int v = target; v != source; v = prevVertex[v])
    {
      Edge &e = graph[prevVertex[v]][prevEdge[v]];
      e.flow -= flow;
      graph[e.to][e.back].flow += flow;
      minCost += flow * e.cost;
    }
  }
  return(make_pair(minCost, totalFlow));
}

int main()
{
  int m;
  while (scanf("%d", &m) && m)
  {
    for (int i = 0; i < 5; i ++) scanf("\n%s", field[i]);
    DEBUG for (int i = 0; i < 5; i ++) printf("%s\n", field[i]);

    int offset = 5*m; target = 2*5*m + 1; vertices = target + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();
    for (int i = 0; i < 5; i ++)
    {
      if (field[i][0] == '@')
        addEdge(source, 1 + i*m + 0, 1, 0);
      addEdge(1 + offset + i*m + m - 1, target, 1, 0);
    }

    for (int i = 0; i < 5; i ++)
      for (int j = 0; j < m; j ++)
      {
        if (j + 1 < m) addEdge(1 + offset + i*m + j, 1 + i*m + j + 1, 1, 0);
        if (i - 1 >= 0) addEdge(1 + offset + i*m + j, 1 + (i - 1)*m + j, 1, 0);
        if (i + 1 < 5) addEdge(1 + offset + i*m + j, 1 + (i + 1)*m + j, 1, 0);
        addEdge(1 + i*m + j, 1 + offset + i*m + j, 1, field[i][j] == '@' ? 0 : field[i][j] - '0');
      }

    pair<int, int> ans = minCostFlow();
    printf("%d\n", ans.first);
    DEBUG printf("%d %d\n", ans.first, ans.second);
  }
  return(0);
}
/*
n = 3, m = 3
1 [1][1] (0*m + 0) 2 [1][2] (0*m + 1) 3 [1][3] (0*m + 2)
5 [2][1] (1*m + 0) 6 [2][2] (1*m + 1) 7 [2][3] (1*m + 2)
8 [3][1] (2*m + 0) 9 [3][2] (2*m + 1) 10 [3][3] (2*m + 2)
*/
