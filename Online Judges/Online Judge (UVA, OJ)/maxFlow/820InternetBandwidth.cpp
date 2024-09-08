#include <bits/stdc++.h>
using namespace std;
int vertices, source, sink, connections;
int matrixGraph[101][101], level[101], inf = 1<<20;

int bfs(vector<int> graph[], int source, int target)
{
  memset(level, -1, sizeof(level));
  level[source] = 0;
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
  int maxFlow = 0, pathFlow = 0;
  while (bfs(graph, source, target))
  {
    do
    {
      pathFlow = dfs(graph, source, target, inf);
      maxFlow += pathFlow;
    } while(pathFlow);
  }
  return(maxFlow);
}

void addEdge(vector<int> graph[], int u, int v, int c)
{
  graph[u].push_back(v);
  matrixGraph[u][v] = matrixGraph[u][v] + c;
  graph[v].push_back(u);
  matrixGraph[v][u] = matrixGraph[v][u] + c;
}

int main()
{
  int network = 1;
  while (scanf("%d", &vertices) != EOF && vertices != 0)
  {
    memset(matrixGraph, 0, sizeof(matrixGraph));
    scanf("%d %d %d", &source, &sink, &connections); source --; sink --;
    vector<int> graph[vertices];
    int u, v, c;
    for (int i = 0; i < connections; i ++)
    {
      scanf("%d %d %d", &u, &v, &c); u --; v --;
      addEdge(graph, u, v, c);
    }

    int maxFlow = dinic(graph, source, sink);
    printf("Network %d\n", network ++);
    printf("The bandwidth is %d.\n\n", maxFlow);
  }
  return(0);
}