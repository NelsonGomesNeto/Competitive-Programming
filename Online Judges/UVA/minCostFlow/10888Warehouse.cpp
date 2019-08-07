#include <bits/stdc++.h>
using namespace std;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char warehouse[40][41];

// source (0) -> warehouse (1 : 40*40) -> target (40*40 + 1)
const int maxVertices = 1 + 40*40 + 1;
int source = 0, target, vertices, inf = 1e7;
int prevVertex[maxVertices], prevEdge[maxVertices], cost[maxVertices], minFlow[maxVertices];
int visited[maxVertices], potentials[maxVertices];
struct Edge { int to, back, flow, capacity, cost; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f, int c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, -c});
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

pair<int, int> minCostFlow()
{
  memset(potentials, 0, sizeof(potentials));
  int minCost = 0, totalFlow = 0;
  while (dijkstraWithPotentials())
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
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, m; scanf("%d %d", &n, &m); target = n*m + 1; vertices = target + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();
    for (int i = 0; i < n; i ++)
    {
      scanf("\n%s", warehouse[i]);
      for (int j = 0; j < m; j ++)
        if (warehouse[i][j] == 'B') addEdge(source, 1 + i*m + j, 1, 0);
        else if (warehouse[i][j] == 'X') addEdge(1 + i*m + j, target, 1, 0);
    }
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        if (warehouse[i][j] == '#') continue;
        else
          for (int k = 0; k < 4; k ++)
          {
            int ni = i + dy[k], nj = j + dx[k];
            if (ni >= 0 && ni < n && nj >= 0 && nj < m && warehouse[ni][nj] != '#')
              addEdge(1 + i*m + j, 1 + ni*m + nj, 16, 1);
          }

    pair<int, int> ans = minCostFlow();
    printf("%d\n", ans.first);
    // printf("%d %d\n", ans.first, ans.second);
  }
  return(0);
}
