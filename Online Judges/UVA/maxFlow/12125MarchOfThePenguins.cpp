#include <bits/stdc++.h>
using namespace std;
const int maxVertices = 100 + 100 + 2;
int matrixGraph[maxVertices][maxVertices], level[maxVertices], inf = 1<<20;

int bfs(vector<int> graph[], int source, int target)
{
  memset(level, -1, sizeof(level)); level[source] = 0;
  deque<int> queue; queue.push_back(source);
  while (!queue.empty())
  {
    int u = queue.front(); queue.pop_front();
    for (auto v: graph[u])
      if (level[v] < 0 && matrixGraph[u][v] > 0)
      {
        level[v] = level[u] + 1;
        queue.push_back(v);
      }
  }
  return(level[target] > 0);
}

int dfs(vector<int> graph[], int u, int target, int flow)
{
  if (u == target) return(flow);
  int actualFlow = 0;
  for (auto v: graph[u])
    if (level[u] + 1 == level[v] && matrixGraph[u][v] > 0)
    {
      int pathFlow = dfs(graph, v, target, min(flow, matrixGraph[u][v]));
      flow -= pathFlow;
      matrixGraph[u][v] -= pathFlow;
      matrixGraph[v][u] += pathFlow;
      actualFlow += pathFlow;
    }
  return(actualFlow);
}

int dinic(vector<int> graph[], int source, int target)
{
  int maxFlow = 0, pathFlow;
  while (bfs(graph, source, target))
    do
    {
      pathFlow = dfs(graph, source, target, inf);
      maxFlow += pathFlow;
    } while (pathFlow);
  return(maxFlow);
}

double dist(int i1[], int i2[])
{
  return(sqrt( pow(i1[0] - i2[0], 2) + pow(i1[1] -  i2[1], 2) ));
}

void addEdge(vector<int> graph[], int u, int v, int c1, int c2)
{
  graph[u].push_back(v);
  matrixGraph[u][v] = c1;
  graph[v].push_back(u);
  matrixGraph[v][u] = c2;
}

void printGraph(vector<int> graph[])
{
  for (int i = 0; i < maxVertices; i ++)
    if (graph[i].size())
    {
      printf("%d", i);
      for (auto j: graph[i])
        printf(" -> (%d, %d)", j, matrixGraph[i][j]);
      printf("\n");
    }
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests -- > 0)
  {
    memset(matrixGraph, 0, sizeof(matrixGraph));
    vector<int> graph[maxVertices];

    int ices; double power; scanf("%d %lf", &ices, &power);
    int ice[ices][4], penguins = 0;
    for (int i = 0; i < ices; i ++)
    {
      for (int j = 0; j < 4; j ++)
        scanf("%d", &ice[i][j]);
      penguins += ice[i][2];
      addEdge(graph, 0, i + 1, ice[i][2], 0);
      addEdge(graph, i + 1, i + 1 + 100, ice[i][3], 0);
      addEdge(graph, i + 1 + 100, maxVertices - 1, inf, inf);
    }

    for (int i = 0; i < ices; i ++)
      for (int j = i + 1; j < ices; j ++)
        if (i != j)
          if (dist(ice[i], ice[j]) <= power)
          {
            //printf("%d %d %lf\n", i, j, dist(ice[i], ice[j]));
            addEdge(graph, i + 1 + 100, j + 1, inf, inf);
            addEdge(graph, j + 1 + 100, i + 1, inf, inf);
          }

    printGraph(graph);
    int maxFlow = dinic(graph, 0, 0 + 1);
    printf("\n%d %d %d\n\n", penguins == maxFlow, penguins, maxFlow);
    printGraph(graph); printf("\n");

  }

  return(0);
}