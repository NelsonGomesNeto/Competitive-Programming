#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int
map<lli, int> numbers;
// source (0) -> a (1, 100) -> b (101, 200) -> target (201)
const int maxVertices = 202;
int matrixGraph[maxVertices][maxVertices], level[maxVertices];
int source = 0, target, inf = 1<<20;

void read(lli a[], int n)
{
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]); int sz = numbers.size();
    if (!numbers.count(a[i])) numbers[a[i]] = sz + 1;
  }
}

int bfs(vector<int> graph[])
{
  memset(level, -1, sizeof(level)); level[source] = 0;
  deque<int> queue; queue.push_back(source);
  while (!queue.empty())
  {
    int u = queue.front(); queue.pop_front();
    for (auto v: graph[u])
      if (matrixGraph[u][v] && level[v] == -1)
        queue.push_back(v), level[v] = level[u] + 1;
  }
  return(level[target] != -1);
}

int dfs(vector<int> graph[], int u, int flow)
{
  if (u == target) return(flow);
  int totalDelivered = 0;
  for (auto v: graph[u])
    if (matrixGraph[u][v] && level[u] == level[v] - 1)
    {
      int delivered = dfs(graph, v, min(flow, matrixGraph[u][v]));
      flow -= delivered;
      matrixGraph[u][v] -= delivered;
      matrixGraph[v][u] += delivered;
      totalDelivered += delivered;
    }
  return(totalDelivered);
}

int dinic(vector<int> graph[])
{
  int maxFlow = 0;
  while (bfs(graph)) maxFlow += dfs(graph, source, inf);
  return(maxFlow);
}

void addEdge(vector<int> graph[], int u, int v, int f)
{
  graph[u].push_back(v);
  matrixGraph[u][v] = f;
  graph[v].push_back(u);
  matrixGraph[v][u] = 0;
}

int main()
{
  int t, r = 1; scanf("%d", &t);
  while (t --)
  {
    numbers.clear(); memset(matrixGraph, 0, sizeof(matrixGraph));
    int n; scanf("%d", &n); lli a[n]; read(a, n);
    int m; scanf("%d", &m); lli b[m]; read(b, m);

    target = n + m + 1;
    vector<int> graph[target + 1];
    for (int i = 0; i < m; i ++)
      if (!matrixGraph[numbers[b[i]]][target]) addEdge(graph, numbers[b[i]], target, 1);
      else matrixGraph[numbers[b[i]]][target] ++;
    for (int i = 0; i < n; i ++)
    {
      if (!matrixGraph[source][numbers[a[i]]]) addEdge(graph, source, numbers[a[i]], 1);
      else matrixGraph[source][numbers[a[i]]] ++;
      for (int j = 0; j < m; j ++)
        if (!matrixGraph[numbers[a[i]]][numbers[b[j]]] && ((a[i] && b[j] % a[i] == 0) || (!a[i] && !b[j])))
          addEdge(graph, numbers[a[i]], numbers[b[j]], 1);
        else if (matrixGraph[numbers[a[i]]][numbers[b[j]]])
          matrixGraph[numbers[a[i]]][numbers[b[j]]] ++;
    }

    DEBUG for (int i = 0; i < target + 1; i ++)
    {
      printf("%d:", i);
      for (auto j: graph[i])
        printf(" (%d, %d)", j, matrixGraph[i][j]);
      printf("\n");
    }

    int maxFlow = dinic(graph);
    printf("Case %d: %d\n", r ++, maxFlow);
  }
  return(0);
}