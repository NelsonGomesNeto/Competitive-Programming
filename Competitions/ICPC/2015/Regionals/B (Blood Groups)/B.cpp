#include <bits/stdc++.h>
using namespace std;

const int maxN = 100; int n, q;
int parents[maxN][maxN + 1], son[maxN + 1];

// source (0) -[1]> parents (1 : n) -[1]> alleles (1 + n : 1 + n + n) -[1]> target (1 + n + n + 1)
// THERE'S A SINGLE CORNER CASE YOU HAVE TO HANDLE:
  // SON WITH 0 ALLELES AND THERE'S A PARENT WITH ALL ALLELES
// Otherwise: flow == needed ? "YES" : "NO"
const int maxV = 1 + maxN + maxN + 1 + 1, inf = 1e6; int source, target, vertices;
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}
void buildGraph()
{
  for (int i = 0; i < vertices; i ++) graph[i].clear();

  for (int i = 0; i < n; i ++) addEdge(source, 1 + i, 1);

  for (int i = 0; i < n; i ++)
    for (int j = 0; j <= n; j ++)
      if (parents[i][j])
        addEdge(1 + i, 1 + n + j, 1);

  for (int j = 0; j <= n; j ++)
    if (son[j])
      addEdge(1 + n + j, target, 1);
}

int level[maxV], ptr[maxV];
bool bfs()
{
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(source); level[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        level[e.to] = level[u] + 1, q.push(e.to);
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

int main()
{
  while (scanf("%d %d", &n, &q) != EOF)
  {
    memset(parents, 0, sizeof(parents)), memset(son, 0, sizeof(son));
    target = 1 + n + n + 1; vertices = target + 1;
    bool hasFullParents = false;
    for (int i = 0; i < n; i ++)
    {
      int b; scanf("%d", &b);
      for (int j = 0, c; j < b; j ++)
      {
        scanf("%d", &c);
        parents[i][c] ++;
      }
      if (b < n) parents[i][0] ++;
      else hasFullParents = true;
    }

    while (q --)
    {
      int b, needed; scanf("%d", &b);
      needed = b;
      memset(son, 0, sizeof(son));
      for (int j = 0, c; j < b; j ++)
      {
        scanf("%d", &c);
        son[c] ++;
      }
      if (b < n) son[0] ++, needed ++;

      if (b == 0 && hasFullParents) printf("N\n");
      else
      {
        buildGraph();
        int flow = dinic();
        // printf("%d %d -- ", flow, needed);
        printf("%c\n", flow == needed ? 'Y' : 'N');
      }
    }
    // printf("---------------------\n");
  }
  return(0);
}