#include <bits/stdc++.h>
using namespace std;

// just a simple graph
// we will run minCostFlow until we reach 2 of flow, very streight forward
const int maxVertices = 100 + 2*100*100, inf = 1e7;
int source, target, vertices;
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
  priority_queue<pair<int, int>> pq;
  cost[source] = 0; pq.push({cost[source], source});
  while (!pq.empty())
  {
    int u = pq.top().second; pq.pop();
    if (visited[u]) continue;
    visited[u] = 1;
    for (int j = 0; j < graph[u].size(); j ++)
    {
      Edge &e = graph[u][j]; int newCost = cost[u] + e.cost + potentials[u] - potentials[e.to];
      if (e.flow && newCost < cost[e.to])
      {
        cost[e.to] = newCost, minFlow[e.to] = min(minFlow[u], e.flow);
        prevVertex[e.to] = u, prevEdge[e.to] = j;
        pq.push({-cost[e.to], e.to});
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
      minCost += e.cost * flow;
    }
  }
  return(make_pair(minCost, totalFlow));
}

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    int m; scanf("%d", &m); int u, v, c;
    source = 0, target = n + 2*m; vertices = n + 2*m + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();
    for (int i = 0; i < m; i ++)
    {
      scanf("%d %d %d", &u, &v, &c); u --, v --;
      addEdge(u, n + i, 1, c);
      addEdge(v, n + i, 1, c);
      addEdge(n + i, n + m + i, 1, 0);
      addEdge(n + m + i, u, 1, 0);
      addEdge(n + m + i, v, 1, 0);
    }
    addEdge(n - 1, target, 2, 0);

    pair<int, int> ans = minCostFlow();
    // printf("ans: %d %d\n", ans.first, ans.second);
    if (ans.second < 2) printf("Back to jail\n");
    else printf("%d\n", ans.first);
  }
  return(0);
}
