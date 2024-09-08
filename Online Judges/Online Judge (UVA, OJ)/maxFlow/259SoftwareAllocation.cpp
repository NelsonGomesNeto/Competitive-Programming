#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
const int maxVertices = 38;
int matrixGraph[maxVertices][maxVertices], level[maxVertices], inf = 1<<20;

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
  int maxFlow = 0;
  while (bfs(graph, source, target))
    maxFlow += dfs(graph, source, target, inf);
  return(maxFlow);
}

void addEdge(vector<int> graph[], int u, int v, int c)
{
  graph[u].push_back(v);
  matrixGraph[u][v] = c;
  graph[v].push_back(u);
}

int main()
{
  int s, test = 0;
  char c, end;
  do
  {
    memset(matrixGraph, 0, sizeof(matrixGraph));
    char software[27][20]; s = 0; end = 0;
    memset(software, '\0', sizeof(software));
    while (scanf("%c", &end) != EOF && end != '\n')
    {
      software[s][0] = end; int i = 1;
      while (scanf("%c", &c) && c != ';')
        software[s][i ++] = c;
      getchar();
      s ++;
    }

    if (s)
    {
      DEBUG {
        printf("Test %d:\n", test); for (int i = 0; i < s; i ++) printf("%s\n", software[i]); }
      test ++;

      int mustAlloc = 0;
      vector<int> graph[maxVertices];
      for (int i = 0; i < s; i ++)
      {
        addEdge(graph, 0, software[i][0] - 'A' + 1, software[i][1] - '0');
        mustAlloc += software[i][1] - '0';
        for (int j = 3; software[i][j]; j ++)
          addEdge(graph, software[i][0] - 'A' + 1, software[i][j] - '0' + 27, 1);
      }
      for (int i = 27; i < 37; i ++)
        addEdge(graph, i, 37, 1);

      int maxFlow = dinic(graph, 0, 37);
      DEBUG printf("maxFlow: %d\n", maxFlow);

      if (maxFlow == mustAlloc)
        for (int i = 0 + 27; i <= 9 + 27; i ++)
        {
          int done = 0;
          for (int j = 1; j < 27; j ++)
            if (matrixGraph[i][j])
            {
              printf("%c", j - 1 + 'A');
              done = 1;
            }
          if (!done) printf("_");
        }
      else printf("!");
      printf("\n");

      DEBUG
        for (int i = 0; i < maxVertices; i ++)
          if (graph[i].size() > 0)
          {
            printf("%d", i);
            for (int u: graph[i])
              if (matrixGraph[i][u])
                printf(" -> (%d, %d)", u, matrixGraph[i][u]);
            printf("\n");
          }
    }
  } while(s && end);

  return(0);
}