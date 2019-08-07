#include <bits/stdc++.h>
using namespace std;
// There are 9592 prime numbers between 1 and 1e5

const int maxVertices = 1e3 + 1 + 9592 + 1 + 1, maxM = 1e5 + 1, inf = 1e8 + 1; int n, m;

// source (0) -> n (1 : n) -> primes (1 + n : 1 + n + 9592) -> target (1 + n + 9592 + 1)
int source = 0, target, vertices;
int level[maxVertices], ptr[maxVertices]; queue<int> q;
struct Edge { int to, back, capacity, flow; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool bfs()
{
  memset(level, -1, sizeof(level));
  q.push(source), level[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (level[e.to] == -1 && e.flow)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}

int dfs(int u, int flow)
{
  if (u == target || !flow) return(flow);
  int delivered;
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (level[u] + 1 == level[e.to] && e.flow)
    {
      delivered = dfs(e.to, min(flow, e.flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered);
    }
  }
  return(0);
}

int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs(source, inf)) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  bool isPrime[maxM]; memset(isPrime, true, sizeof(isPrime));
  isPrime[1] = 0;
  for (int i = 2; i <= maxM; i ++)
    for (int j = 2; i * j <= maxM; j ++)
      isPrime[i * j] = false;
  vector<int> primes;
  for (int i = 1; i <= maxM; i ++) if (isPrime[i]) primes.push_back(i);

  scanf("%d %d", &n, &m); target = 1 + n + 9592 + 1; vertices = target + 1;
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  for (int i = 0; i < n; i ++)
    addEdge(source, 1 + i, 1);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < primes.size() && primes[j] <= m; j ++)
      if (a[i] % primes[j] == 0)
        addEdge(1 + i, 1 + n + j, 1);
  for (int j = 0; j < primes.size() && primes[j] <= m; j ++)
    addEdge(1 + n + j, target, 1);
  printf("%d\n", dinic());

  return(0);
}