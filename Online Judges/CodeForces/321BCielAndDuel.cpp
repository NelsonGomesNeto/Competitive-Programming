#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
// source (0) -> ciel (1 : m) -> jiro (1 + m : m + n) -> target (m + n + 1)
// connection will be if ciel's card can kill jiro's card
// there are two possible scenarios:
  // we can't kill all the cards, therefore, we better kill the attacking ones, since only with those we can inflinge damage
  // we can kill all the cards, therefore, we attempt to kill all of them, and in that already try to hit directly
// the only difference is that we aren't aiming minCostFlow, but a maxCostFlow, which can be achieved by setting all costs to negative ^~^
const int maxVertices = 1 + 100 + 100 + 1;
int source = 0, target, vertices, inf = 1e7;
int prevVertice[maxVertices], prevEdge[maxVertices], cost[maxVertices], minFlow[maxVertices];
struct Edge { int to, back, flow, capacity, cost; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f, int c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, -c});
}
char jiroCardsMode[100][4]; int jiroCardsStrength[100], cielCardsStrength[100], n, m;

void initGraph()
{
  for (int i = 0; i < vertices; i ++) graph[i].clear();
  for (int i = 0; i < m; i ++) addEdge(source, 1 + i, 1, 0);
  for (int i = 0; i < n; i ++) addEdge(1 + m + i, target, 1, 0);
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
          prevVertice[e.to] = u, prevEdge[e.to] = j;
          minFlow[e.to] = min(minFlow[u], e.flow);
          done = 1;
        }
      }
    if (!done) break;
  }
  return(cost[target] != inf);
}

pair<int, int> minCostFlow(bool maxFlow)
{
  int minCost = 0, totalFlow = 0;
  while (bellmanFord())
  {
    // because the min (which is max in this case) cost is a priority over max flow
    // therefore, if it starts to increase cost in order to increase flow: we stop it
    if (!maxFlow && cost[target] > 0) break;
    int flow = minFlow[target];
    totalFlow += flow;
    for (int v = target; v != source; v = prevVertice[v])
    {
      Edge &e = graph[prevVertice[v]][prevEdge[v]];
      e.flow -= flow;
      graph[e.to][e.back].flow += flow;
      minCost += e.cost * flow;
    }
  }
  return(make_pair(minCost, totalFlow));
}

int main()
{
  scanf("%d %d", &n, &m); target = m + n + 1; vertices = target + 1;
  for (int i = 0; i < n; i ++)
    scanf("\n%s %d", jiroCardsMode[i], &jiroCardsStrength[i]);
  for (int i = 0; i < m; i ++)
    scanf("%d", &cielCardsStrength[i]);

  // not kill all
  initGraph();
  for (int i = 0; i < m; i ++)
    for (int j = 0; j < n; j ++)
      if (!strcmp(jiroCardsMode[j], "ATK") && cielCardsStrength[i] >= jiroCardsStrength[j])
        addEdge(1 + i, 1 + m + j, 1, -(cielCardsStrength[i] - jiroCardsStrength[j]));
  pair<int, int> notKillAll = minCostFlow(false), killAll = {0, 0};
  DEBUG printf("%d %d\n", notKillAll.first, notKillAll.second);

  // kill all
  if (m > n) // ciel has enough cards to kill all jiro's cards and inflict direct damage
  {
    target = m + m + 1; vertices = target + 1; initGraph();
    for (int i = n; i < m; i ++) addEdge(1 + m + i, target, 1, 0);
    for (int i = 0; i < m; i ++)
      for (int j = 0; j < m; j ++)
      {
        if (j >= n) addEdge(1 + i, 1 + m + j, 1, -cielCardsStrength[i]);
        else if (!strcmp(jiroCardsMode[j], "ATK") && cielCardsStrength[i] >= jiroCardsStrength[j])
          addEdge(1 + i, 1 + m + j, 1, -(cielCardsStrength[i] - jiroCardsStrength[j]));
        else if (!strcmp(jiroCardsMode[j], "DEF") && cielCardsStrength[i] > jiroCardsStrength[j])
          addEdge(1 + i, 1 + m + j, 1, 0);
      }
    killAll = minCostFlow(true);
    DEBUG printf("%d %d\n", killAll.first, killAll.second);
  }

  int damage = -notKillAll.first;
  if (m > n && killAll.second == m) // could kill all
    damage = max(damage, -killAll.first);
  printf("%d\n", damage);

  return(0);
}
