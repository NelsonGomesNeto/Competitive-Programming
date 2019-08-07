#include <bits/stdc++.h>
#define lli long long int
using namespace std;
const int maxSize = 200 + 200 + 2 + 1;
int n, m, k; lli inf = 1e18;
lli matrixGraph[maxSize][maxSize][2];
// source -> team (n) -> check (m) -> target

void read(int a[][2], int n)
{
  for (int i = 0; i < n; i ++) scanf("%d %d", &a[i][0], &a[i][1]);
}

void addEdge(vector<int> graph[], int u, int v, int f, int c)
{
  graph[u].push_back(v);
  matrixGraph[u][v][0] = f, matrixGraph[u][v][1] = c;
  graph[v].push_back(u);
  matrixGraph[v][u][0] = 0, matrixGraph[v][u][1] = -c;
}

double distance(int a[], int b[], double s)
{
  double x = a[0], y = a[1], p = b[0], q = b[1];
  return(ceil(((p-x)*(p-x) + (q-y)*(q-y)) / (s * s)));
}

int bellmannFord(vector<int> graph[], int prev[], int source, int target)
{
  lli cost[maxSize]; for (int i = 0; i < maxSize; i ++) cost[i] = inf;
  cost[source] = 0;
  for (int i = 0; i < n + m + 2 + 1 - 1; i ++)
  {
    int done = 0;
    for (int u = 0; u < n + m + 2 + 1; u ++)
      for (auto v: graph[u])
        if (matrixGraph[u][v][0] && max(cost[u], matrixGraph[u][v][1]) < cost[v])
        {
          cost[v] = max(cost[u], matrixGraph[u][v][1]);
          prev[v] = u;
          done = 1;
        }
    if (!done) break;
  }
  return(cost[target] != inf);
}

void minCostFlow(vector<int> graph[], lli *maxFlow, lli *minCost, int source, int target)
{
  int prev[maxSize];
  while (bellmannFord(graph, prev, source, target))
  {
    int v = target; lli flow = inf, cost = 0;
    while (v != source)
    {
      flow = min(flow, matrixGraph[prev[v]][v][0]);
      cost = max(cost, matrixGraph[prev[v]][v][1]);
      v = prev[v];
    }

    *maxFlow += flow;
    *minCost = max(*minCost, cost);
    v = target;
    while (v != source)
    {
      matrixGraph[prev[v]][v][0] -= flow;
      matrixGraph[v][prev[v]][0] += flow;
      v = prev[v];
    }
  }
}

int main()
{
  memset(matrixGraph, 0, sizeof(matrixGraph));
  scanf("%d %d %d", &n, &m, &k);
  int teamPos[n][2], checkPos[m][2], teamSpeed[n];
  read(teamPos, n); read(checkPos, m);
  for (int i = 0; i < n; i ++) scanf("%d", &teamSpeed[i]);

  vector<int> graph[maxSize];
  for (int i = 0; i < n; i ++) addEdge(graph, 0, i + 1, 1, 0);
  for (int i = 0; i < m; i ++) addEdge(graph, i + n + 1, n + m + 1, 1, 0);
  for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++)
    addEdge(graph, i + 1, j + n + 1, 1, distance(teamPos[i], checkPos[j], teamSpeed[i]));
  addEdge(graph, n + m + 1, n + m + 2, k, 0);

  lli maxFlow = 0, minCost = 0; minCostFlow(graph, &maxFlow, &minCost, 0, m + n + 2);
  printf("%lld\n", minCost);

  return(0);
}