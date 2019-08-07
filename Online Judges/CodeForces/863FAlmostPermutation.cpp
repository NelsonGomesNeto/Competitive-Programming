#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

/* Explanation:
Each number will have n connections to the source, the cost will be (1 + 2 * i)
  Where i is the i-th connection of the number
  So the costs will be: 1, 3, 5, 9, ...; note that k flow will rise cost to k^2
Pre-calculate the minimum and maximum of each position
For each position (p), for each number (num) between minimum and maximum of position p
  Make a connection from num to p
And connect each position to the target
Run minCostFlow: gg
*/

// source (0) -> numbers (1 : n) -> position (n + 1 : 2 * n) -> target (2 * n + 1)
const int maxVertices = 1 + 2 * 100 + 1;
int source = 0, target, vertices, inf = 1e7;
int cost[maxVertices], minFlow[maxVertices], prevVertex[maxVertices], prevEdge[maxVertices], potentials[maxVertices], visited[maxVertices];
struct Edge { int to, back, capacity, flow, cost; };
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
  priority_queue<pair<int, int>> pq; pq.push({0, source}); cost[source] = 0;
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
        cost[e.to] = newCost;
        minFlow[e.to] = min(minFlow[u], e.flow);
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
      minCost += flow * e.cost;
    }
  }
  return(make_pair(minCost, totalFlow));
}

int main()
{
  int n, q; scanf("%d %d", &n, &q); target = 2 * n + 1; vertices = target + 1;
  int restrictions[q][4], minimum[n], maximum[n]; for (int i = 0; i < n; i ++) minimum[i] = 1, maximum[i] = n;
  for (int i = 0; i < q; i ++)
  {
    for (int j = 0; j < 4; j ++) scanf("%d", &restrictions[i][j]);
    for (int k = restrictions[i][1] - 1; k < restrictions[i][2]; k ++)
      if (restrictions[i][0] == 1)
        minimum[k] = max(minimum[k], restrictions[i][3]);
      else
        maximum[k] = min(maximum[k], restrictions[i][3]);
  }
  // for (int i = 0; i < n; i ++) printf("(%d, %d)%c", minimum[i], maximum[i], i < n - 1 ? ' ' : '\n');
  for (int i = 1; i <= n; i ++)
    for (int j = 0; j < n; j ++)
      addEdge(source, i, 1, 2 * j + 1);
  for (int i = 0; i < n; i ++)
    for (int k = minimum[i]; k <= maximum[i]; k ++)
      addEdge(k, 1 + n + i, 1, 0);
  for (int i = n + 1; i <= 2 * n; i ++) addEdge(i, target, 1, 0);

  DEBUG for (int i = 0; i < vertices; i ++)
  {
    printf("%d:", i);
    for (auto &e: graph[i]) printf(" %d", e.to);
    printf("\n");
  }

  pair<int, int> ans = minCostFlow();
  // printf("%d %d\n", ans.first, ans.second);
  printf("%d\n", ans.second == n ? ans.first : -1);

  return(0);
}