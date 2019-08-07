#include <bits/stdc++.h>
using namespace std;
const int maxVertices = 200 + 2;
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

void addEdge(vector<int> graph[], int u, int v, int c)
{
  graph[u].push_back(v);
  matrixGraph[u][v] = c;
  graph[v].push_back(u);
  matrixGraph[v][u] = 0;
}

int main()
{
  int regulators, limitation;
  while (scanf("%d", &regulators) != EOF)
  {
    vector<int> graph[maxVertices];
    for (int i = 0; i < regulators; i ++)
    {
      scanf("%d", &limitation);
      addEdge(graph, i + 1, i + 100 + 1, limitation);
    }

    int connections, u, v, c; scanf("%d", &connections);
    for (int i = 0; i < connections; i ++)
    {
      scanf("%d %d %d", &u, &v, &c);
      addEdge(graph, u + 100, v, c);
    }

    int fromFont, toSink; scanf("%d %d", &fromFont, &toSink);
    for (int i = 0; i < fromFont + toSink; i ++)
    {
      scanf("%d", &u);
      if (i < fromFont) addEdge(graph, 0, u, inf);
      else addEdge(graph, u + 100, maxVertices - 1, inf);
    }

    int maxFlow = dinic(graph, 0, maxVertices - 1);
    printf("%d\n", maxFlow);
  }

  return(0);
}