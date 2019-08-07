#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
char f[10][11]; const int maxVertices = 2 * (10 * 10) + 2;
int matrixGraph[maxVertices][maxVertices], level[maxVertices];
int source, sink, n, m, inf = 1<<20;
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int valid(int i, int size)
{
  return(!(i < 0 || i >= size));
}

void addEdge(vector<int> graph[], int u, int v, int c)
{
  graph[u].push_back(v); matrixGraph[u][v] = c;
  graph[v].push_back(u); matrixGraph[v][u] = 0;
}

void printGraph(vector<int> graph[], int size)
{
  for (int i = 0; i < size; i ++)
    if (graph[i].size())
    {
      printf("%d", i);
      for (auto u: graph[i])
        printf(" -> %d", u);
      printf("\n");
    }
}

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
    if (level[u] == level[v] - 1 && matrixGraph[u][v] > 0)
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
  {
    pathFlow = dfs(graph, source, target, inf);
    maxFlow += pathFlow;
  }
  return(maxFlow);
}

int main()
{
  memset(matrixGraph, 0, sizeof(matrixGraph));
  scanf("%d %d", &n, &m);
  source = 0; sink = 2 * (n * m) + 1;
  for (int i = 0; i < n; i ++) scanf("\n%s", f[i]);

  vector<int> graph[sink + 1];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      if (f[i][j] == 'P')
        addEdge(graph, n*m + (i*m + j) + 1, sink, 1);
      else if (f[i][j] == 'W')
      {
        addEdge(graph, 0, (i*m + j) + 1, 1);
        for (int k = 0; k < 4; k ++)
          if (valid(i + dy[k], n) && valid(j + dx[k], m) && f[i + dy[k]][j + dx[k]] == 'P')
            addEdge(graph, (i*m + j) + 1, n*m + ((i+dy[k])*m + (j+dx[k])) + 1, 1);
      }
  DEBUG printGraph(graph, sink + 1);

  printf("%d\n", dinic(graph, 0, sink));
  return(0);
}
