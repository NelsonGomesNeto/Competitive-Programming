#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

// source (0) -[1, 0]> a (1 : n) -[1, xcost(i, i)]> b (1 + n : 2*n) -[1, 0]> sink (1 + 2*n)
//                               -[1, y / 2 + xcost(i, j)]>
const int maxVertices = 1e5;
int source, sink, vertices; lli inf = LONG_LONG_MAX;
lli cost[maxVertices];
int prevVertex[maxVertices], prevEdge[maxVertices], minFlow[maxVertices];
int inqueue[maxVertices]; // needed for SPFA
lli potentials[maxVertices]; int visited[maxVertices]; // needed for Dijkstra with Potentials
// Dijkstra with Potentials is faster then SPFA
// But can't be used if there are negative edges at the start

struct Edge { int to, back, flow, capacity; lli cost; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f, lli c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, -c});
}
void printGraph()
{
  printf("\ncost: %lld\n", cost[sink]);
  lli totalCost = 0;
  for (int v = sink; v != source; v = prevVertex[v])
  {
    totalCost += graph[prevVertex[v]][prevEdge[v]].cost;
    printf("%d%s", v, prevVertex[v] != source ? " <- " : " <- 0");
    if (prevVertex[v] == source) printf(" | totalCost: %lld\n", totalCost);
  }
  // for (int i = 0; i < vertices; i ++)
  // {
  //   printf("%2d (pot: %2d):", i, potentials[i]); int k = 0;
  //   for (Edge &e: graph[i])
  //     printf(" (%2d, %2d, %3d)", e.to, e.flow, e.cost);
  //   printf("\n");
  // }
}

// bool SPFA()
// {
//   memset(inqueue, 0, sizeof(inqueue));
//   for (int i = 0; i < vertices; i ++) cost[i] = inf, minFlow[i] = 1e7;
//   deque<int> q; q.push_back(source); cost[source] = 0;
//   while (!q.empty())
//   {
//     int u = q.front(); q.pop_front(); inqueue[u] = 0;
//     for (int j = 0; j < graph[u].size(); j ++)
//     {
//       Edge &e = graph[u][j]; lli newCost = cost[u] + e.cost;
//       if (e.flow && newCost < cost[e.to])
//       {
//         if (!inqueue[e.to]) inqueue[e.to] = 1, q.push_back(e.to);
//         cost[e.to] = newCost;
//         minFlow[e.to] = min(minFlow[u], e.flow);
//         prevVertex[e.to] = u, prevEdge[e.to] = j;
//       }
//     }
//   }
//   return(cost[sink] != inf);
// }

bool dijkstraWithPotentials()
{
  memset(visited, 0, sizeof(visited));
  for (int i = 0; i < vertices; i ++) cost[i] = inf, minFlow[i] = 1e7;
  priority_queue<pair<lli, int>> q;
  q.push({0, source}); cost[source] = 0;
  while (!q.empty())
  {
    int u = q.top().second; q.pop();
    if (visited[u]) continue;
    visited[u] = 1;
    for (int j = 0; j < graph[u].size(); j ++)
    {
      Edge &e = graph[u][j]; lli newCost = cost[u] + e.cost + potentials[u] - potentials[e.to];
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
  return(cost[sink] != inf);
}

pair<lli, int> minCostFlow()
{
  memset(potentials, 0, sizeof(potentials));
  lli minCost = 0; int totalFlow = 0;
  while (dijkstraWithPotentials())
  {
    DEBUG printGraph();
    int flow = minFlow[sink];
    totalFlow += flow;
    for (int v = sink; v != source; v = prevVertex[v])
    {
      Edge &e = graph[prevVertex[v]][prevEdge[v]];
      e.flow -= flow;
      graph[e.to][e.back].flow += flow;
      minCost += flow * e.cost;
    }
  }
  return(make_pair(minCost, totalFlow));
}

const int maxN = 18; int n; lli x, y;
lli a[maxN], b[maxN];

lli xCost(int i, int j)
{
  return abs(a[i] - b[j]) * x;
}

int main()
{
  while (~scanf("%d %lld %lld", &n, &x, &y))
  {
    x *= 2, y *= 2;
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++) scanf("%lld", &b[i]);

    source = 0, sink = 2*n + 1, vertices = 2*n + 2;
    for (int i = 0; i < vertices; i++) graph[i].clear();

    for (int i = 0; i < n; i++)
      addEdge(source, 1 + i, 1, 0);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        addEdge(1 + i, 1 + n + j, 1, (y / 2 * abs(i - j)) + xCost(i, j));

    for (int i = 0; i < n; i++)
      addEdge(1 + n + i, sink, 1, 0);

    pair<lli, int> res = minCostFlow();
    printf("%lld\n", res.first >> 1LL);
  }
  return 0;
}
