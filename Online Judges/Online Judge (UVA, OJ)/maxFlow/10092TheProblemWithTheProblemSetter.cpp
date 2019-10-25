#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int matrixGraph[1022][1022], level[1022], inf = 1<<20;

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
    }
    while (pathFlow);
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
  int categories, problems;
  while (scanf("%d %d", &categories, &problems) != EOF && !(categories == 0 && problems == 0))
  {
    memset(matrixGraph, 0, sizeof(matrixGraph));
    vector<int> graph[1022];

    int categorie[categories], problemsToAssign = 0;
    for (int i = 0; i < categories; i ++)
    {
      scanf("%d", &categorie[i]); problemsToAssign += categorie[i];
      addEdge(graph, problems + i + 1, 1021, categorie[i]);
    }

    int belongs, problem[problems][categories];
    for (int i = 0; i < problems; i ++)
    {
      addEdge(graph, 0, i + 1, 1);
      scanf("%d", &belongs);
      for (int j = 0; j < belongs; j ++)
      {
        scanf("%d", &problem[i][j]);
        addEdge(graph, i + 1, problems + problem[i][j], 1);
      }
    }

    int maxFlow = dinic(graph, 0, 1021);
    DEBUG printf("%d %d\n", maxFlow, maxFlow == problemsToAssign);
    printf("%d\n", maxFlow == problemsToAssign);
    if (maxFlow == problemsToAssign)
      for (int i = problems + 1; i <= problems + categories; i ++)
      {
        for (auto j: graph[i])
          if (matrixGraph[i][j])
            printf("%d%c", j, (-- maxFlow) ? ' ' : '\0');
        printf("\n");
      }
  }
  return(0);
}