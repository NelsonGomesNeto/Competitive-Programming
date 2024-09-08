#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
const int maxVertices = 50 + 50 + 1;
int matrixGraph[maxVertices][maxVertices], backUp[maxVertices][maxVertices], level[maxVertices], inf = 1<<20;

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
  int maxFlow = 0;
  while (bfs(graph, source, target))
    maxFlow += dfs(graph, source, target, inf);
  return(maxFlow);
}

void addEdge(vector<int> graph[], int u, int v, int c1, int c2)
{
  graph[u].push_back(v);
  matrixGraph[u][v] = c1;
  graph[v].push_back(u);
  matrixGraph[v][u] = c2;
}

vector<pair<int, int> > getCuttedEdges(vector<int> graph[], int source)
{
  int visited[maxVertices]; memset(visited, 0, sizeof(visited));
  deque<int> queue; queue.push_back(source);
  vector<pair<int, int> > aux, cutted;
  while (!queue.empty())
  {
    int u = queue.front(); queue.pop_front();
    if (visited[u]) continue;
    visited[u] = 1;
    for (auto v: graph[u])
      if (matrixGraph[u][v] > 0) queue.push_back(v);
      else aux.push_back({u, v});
  }
  for (auto i: aux)
    if (!visited[i.second]) cutted.push_back(i);
  return(cutted);
}

int main()
{
  int computers, connections;
  while (scanf("%d %d", &computers, &connections) && !(computers == 0 && connections == 0))
  {
    memset(matrixGraph, 0, sizeof(matrixGraph));
    vector<int> graph[maxVertices];
    int pos, cost;
    addEdge(graph, 1, 1 + 50, inf, 0);
    for (int i = 1; i < computers - 1; i ++)
    {
      scanf("%d %d", &pos, &cost);
      addEdge(graph, pos, pos + 50, cost, 0);
    }
    addEdge(graph, computers, computers + 50, inf, 0);

    int u, v, c;
    for (int i = 0; i < connections; i ++)
    {
      scanf("%d %d %d", &u, &v, &c);
      addEdge(graph, u + 50, v, c, 0);
      addEdge(graph, v + 50, u, c, 0); // FREAKING, I FORGOT THE BIDIRECTION
    }

    DEBUG {
      for (int i = 1; i < maxVertices; i ++)
      if (graph[i].size())
      {
        printf("%d", i);
        for (auto j: graph[i])  printf(" -> (%d, %d)", j, matrixGraph[i][j]);
        printf("\n");
      }
    }

    // memcpy(backUp, matrixGraph, sizeof(matrixGraph));
    int maxFlow = dinic(graph, 1, computers + 50);
    // DEBUG printf("maxFlow: %d\n", maxFlow);
    // vector<pair<int, int> > cutted = getCuttedEdges(graph, 1);
    // int cuttedFlow = 0;
    // for (auto i: cutted)
    // {
    //   DEBUG printf("%d %d (%d, %d)\n", i.first, i.second, backUp[i.first][i.second], backUp[i.second][i.first]);
    //   cuttedFlow += backUp[i.first][i.second];
    // }
    // DEBUG printf("cuttedFlow: %d\n", cuttedFlow);
    printf("%d\n", maxFlow);
  }
  return(0);
}