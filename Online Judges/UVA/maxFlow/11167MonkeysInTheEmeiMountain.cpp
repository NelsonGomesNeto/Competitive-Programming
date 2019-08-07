#include <bits/stdc++.h>
#define DEBUG if(1)
using namespace std;
const int maxVertices = 2 + 100 + 100000;
int **matrixGraph; int level[maxVertices], inf = 1<<20;

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
  matrixGraph[v][u] = 0;
}

int main()
{
  matrixGraph = (int**) malloc(maxVertices * sizeof(int*));
  for (int i = 0; i < maxVertices; i ++)
    matrixGraph[i] = (int*) malloc(maxVertices * sizeof(int));

  int monkeys, canDrink, test = 1;
  while (scanf("%d %d", &monkeys, &canDrink) != EOF && !(monkeys == 0))
  {
    vector<int> graph[maxVertices];
    for (int i = 100; i < 50100; i ++)
    {
      addEdge(graph, i, i + 50000, canDrink);
      addEdge(graph, i + 50000, maxVertices - 1, inf);
    }

    int toDrink = 0, monkey[monkeys][2];
    for (int i = 0; i < monkeys; i ++)
    {
      int v, a, b; scanf("%d %d %d", &v, &a, &b);
      monkey[i][0] = a; monkey[i][1] = b;
      toDrink += v;
      addEdge(graph, 0, i + 1, v);
      for (int j = a; j <= b - 1; j ++)
        addEdge(graph, i + 1, j + 100, 1);
    }

    int maxFlow = dinic(graph, 0, maxVertices - 1);

    printf("Case %d: %s\n", test ++, maxFlow == toDrink ? "Yes" : "No");
    if (maxFlow == toDrink)
      for (int i = 0; i < monkeys; i ++)
      {
        int drink[maxVertices][2], at = 0;
        for (int j = monkey[i][0]; j < monkey[i][1]; j ++)
          //printf("%d %d (%d)\n", i, j, matrixGraph[j + 100][i + 1]);
          if (matrixGraph[j + 100][i + 1])
          {
            drink[at][0] = j;
            while (j < monkey[i][1] && matrixGraph[j + 100][i + 1])
              j ++;
            drink[at ++][1] = j;
          }
        printf("%d", at);
        for (int j = 0; j < at; j ++) printf(" (%d,%d)", drink[j][0], drink[j][1]);
        printf("\n");
      }
  }

  return(0);
}
