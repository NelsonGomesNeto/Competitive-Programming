#include <bits/stdc++.h>
using namespace std;
const int maxVertices = 30 + 8;
int matrixGraph[maxVertices][maxVertices], level[maxVertices], inf = 1<<20;
map<string, int> sizeToInt = {{"XS", 0}, {"S", 1}, {"M", 2}, {"L", 3}, {"XL", 4}, {"XXL", 5}};

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
  {
    if (level[u] + 1 == level[v] && matrixGraph[u][v] > 0)
    {
      int pathFlow = dfs(graph, v, target, min(flow, matrixGraph[u][v]));
      flow -= pathFlow;
      matrixGraph[u][v] -= pathFlow;
      matrixGraph[v][u] += pathFlow;
      actualFlow += pathFlow;
    }
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
  int tests; scanf("%d", &tests);
  while (tests -- > 0)
  {
    int tshirts, volunteers; scanf("%d %d", &tshirts, &volunteers);
    vector<int> graph[volunteers + 8];

    string kind;
    for (int i = 0; i < volunteers; i ++)
    {
      addEdge(graph, 0, i + 1, 1);
      for (int j = 0; j < 2; j ++)
      {
        getchar();
        cin >> kind;
        addEdge(graph, i + 1, sizeToInt[kind] + volunteers + 1, 1);
      }
    }

    for (int i = volunteers + 1; i < volunteers + 7; i ++)
      addEdge(graph, i, volunteers + 7, tshirts / 6);

    int maxFlow = dinic(graph, 0, volunteers + 7);

    printf("%s\n", maxFlow == volunteers ? "YES" : "NO");
  }
  return(0);
}