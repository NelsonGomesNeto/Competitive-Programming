#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxK = 100, maxN = 5e3, maxV = 2*5e3 + 1, inf = 1e9; int k, n;
// source (0) -> graph (but with vertice flow trick 1 : 2*n) -> target (2*n + 1)
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxV]; int source = 0, target, vertices;
int level[maxV], ptr[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool bfs()
{
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(source), level[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}
int dfs(int u = source, int flow = inf)
{
  if (!flow || u == target) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[e.to] == level[u] + 1)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
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
    while (flow = dfs()) maxFlow += flow;
  }
  return(maxFlow);
}

int prv[maxV];
bool visited[maxV];
bool pathDfs(int u = target)
{
  // printf("%d\n", u);
  if (u == source) return(true);
  visited[u] = true;
  for (Edge &e: graph[u])
    if (e.flow && !e.capacity && !visited[e.to] && pathDfs(e.to))
    {
      prv[e.to] = u;
      return(true);
    }
  return(false);
}
void printPath()
{
  visited[source] = visited[target] = visited[1] = visited[2] = visited[n + 1] = visited[n + 2] = false;
  pathDfs();
  for (int u = 1; u != 2; u = prv[u])
    if (u <= n)
      printf("%d ", u);
  printf("2\n");
}

int main()
{
  int t = 0;
  while (scanf("%d %d", &k, &n) != EOF && !(!n && !k))
  {
    if (t ++) printf("\n");
    target = 2*n + 1; vertices = target + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();
    for (int i = 1; i <= n; i ++)
    {
      int u; char end;
      while (scanf("%d%c", &u, &end) && end != '\n')
        addEdge(n + i, u, 1);
      addEdge(n + i, u, 1);
    }
    for (int i = 1; i <= n; i ++)
      addEdge(i, n + i, i <= 2 ? k : 1);
    addEdge(source, 1, k), addEdge(n + 2, target, k);


    int flow = dinic();
    // for (int i = 0; i < vertices; i ++)
    // {
    //   printf("%d -", i);
    //   for (Edge &e: graph[i])
    //     if (e.capacity == 0) printf(" (%d, %d, %d)", e.to, e.flow, e.capacity);
    //   printf("\n");
    // }
    printf("Case %d:\n", t);
    // printf("Case %d: || %d\n", t, flow);
    if (flow == k)
    {
      memset(visited, false, sizeof(visited));
      for (int i = 0; i < k; i ++)
        printPath();
    }
    else printf("Impossible\n");
  }
  return(0);
}