#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

// This only works for bipartite graphs
const int maxV = 1e5, inf = 1e9;
vector<int> lefts, rights;
int source, sink, vertices, level[maxV], ptr[maxV];
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxV];
void addEdge(int u, int v)
{
  graph[u].push_back({v, (int) graph[v].size(), 1, 1});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool bfs()
{
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(source); level[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return level[sink] != -1;
}
int dfs(int u = source, int flow = inf)
{
  if (u == sink || !flow) return flow;
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[e.to] == level[u] + 1)
    {
      int delivered = dfs(e.to, min(e.flow, flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return delivered;
    }
  }
  return 0;
}
int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs()) maxFlow += flow;
  }
  return maxFlow;
}

bool visited[maxV];
vector<int> minimumVertexCover()
{
  dinic();
  // MVC = {rights visited (starting from unmatched lefts)} + {lefts unvisited}
  memset(visited, false, sizeof(visited));
  vector<int> ans;
  queue<int> q;
  // unmatched lefts
  for (int i = 1; i <= lefts.size(); i ++)
  {
    bool unmatched = true;
    for (Edge &e: graph[i])
      if (e.to != source && !e.flow)
        unmatched = false;
    if (unmatched) q.push(i);
  }
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (visited[u]) continue;
    visited[u] = true;
    for (Edge &e: graph[u])
      // lefts to rights has flow if is unmatched
      // rights to lefts hasn't flow if is matched
      if (e.to != source && e.to != sink && e.flow)
        q.push(e.to);
  }
  // rights visited
  for (int i = 1 + lefts.size(); i <= lefts.size() + rights.size(); i ++)
    if (visited[i])
      ans.push_back(i);
  // lefts unvisited
  for (int i = 1; i <= lefts.size(); i ++)
    if (!visited[i])
      ans.push_back(i);
  return ans;
}


int main()
{
  int l, r, m; scanf("%d %d %d", &l, &r, &m);
  sink = 1 + l + r; vertices = sink + 1;
  for (int i = 0; i < l; i ++)
    lefts.push_back(i + 1), addEdge(source, 1 + i);
  for (int i = 0; i < m; i ++)
  {
    int u, v; scanf("%d %d", &u, &v);
    addEdge(u, lefts.size() + v);
  }
  for (int i = 0; i < r; i ++)
    rights.push_back(i + 1), addEdge(1 + lefts.size() + i, sink);

  vector<int> mvc = minimumVertexCover();
  printf("%d\n", (int) mvc.size());
  for (int i = 0; i < mvc.size(); i ++)
    printf("%c%d%c", mvc[i] <= lefts.size() ? 'L' : 'R', mvc[i] <= lefts.size() ? lefts[mvc[i] - 1] : rights[mvc[i] - lefts.size() - 1], i < mvc.size() - 1 ? ' ' : '\n');

  return 0;
}

