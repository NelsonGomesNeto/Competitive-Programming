#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
const int maxVertices = 50 + 2;
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
  matrixGraph[v][u] = c;
}

/* In order to find the Min Cut, we need to perform a Max Flow, and them run a BFS/DFS from source throught the edges with capacity > 0, and the cutted ones will be the ones that have capacity == 0 and are connected to a unreachable vertice */
vector<pair<int, int> > findCuttedEdges(vector<int> graph[], int source, int vertices)
{
  int visited[maxVertices]; memset(visited, 0, sizeof(visited));
  vector<pair<int, int> > cutted, trullyCutted;
  deque<int> queue; queue.push_back(source);
  while (!queue.empty())
  {
    int u = queue.front(); queue.pop_front();
    if (visited[u]) continue;
    visited[u] = 1;
    for (auto v: graph[u])
    {
      if (matrixGraph[u][v] > 0)
        queue.push_back(v);
      else if (!visited[v])
        cutted.push_back({u, v});
    }
  }
  for (int i = 0; i < cutted.size(); i ++)
    if (!visited[cutted[i].second])
      trullyCutted.push_back({cutted[i].first, cutted[i].second});
    //if (visited[cutted[i].second]) cutted.erase(cutted.begin() + i);
  return(trullyCutted);
}

int main()
{
  int cities, connections, run = 0;
  while (scanf("%d %d", &cities, &connections) && !(cities == 0 && connections == 0))
  {
    if (run ++ > 0) printf("\n");

    memset(matrixGraph, 0, sizeof(matrixGraph));
    vector<int> graph[maxVertices];
    int u, v, c;
    for (int i = 0; i < connections; i ++)
    {
      scanf("%d %d %d", &u, &v, &c);
      addEdge(graph, u, v, c);
    }

    int maxFlow = dinic(graph, 1, 2);
    DEBUG {
      printf("%d\n", maxFlow);
      for (int i = 1; i <= cities; i ++)
      {
        printf("%d", i);
        for (auto j: graph[i]) printf(" -> (%d, %d)", j, matrixGraph[i][j]);
        printf("\n");
      }
    }

    vector<pair<int, int> > cutted = findCuttedEdges(graph, 1, cities);
    for (auto i: cutted)
      printf("%d %d\n", i.first, i.second);
  }
  return(0);
}