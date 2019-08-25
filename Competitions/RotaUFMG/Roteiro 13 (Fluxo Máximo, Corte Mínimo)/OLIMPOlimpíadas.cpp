#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  The big problem is that people will move daily. So we can't just find
  the maximum flow and simply divide it by the number of people

  We could emulate that if we had the flows paths
    So, we run any max flow algorithm and then apply a bfs from the target
    to the source (going through used edges and marking them)
  Once we have that, we can search for the day:
    The total flow received from each path in a day:
      flow * (day - distance + 1)
    So, ans == the first day where the sum will be greater or equal to a
*/

const int maxN = 50, maxV = 50 + 1; int n, m, a;
const int inf = 1e9;
// source (1) -[s]> graph (1 : n - 1) -[s]> target (n)
int source = 1, target, vertices;
int ptr[maxV], level[maxV];
struct Edge { int to, back, capacity, flow; };
vector<Edge> graph[maxV];
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
  return level[target] != -1;
}
int dfs(int u = source, int flow = inf)
{
  if (u == target || !flow) return flow;
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[e.to] == level[u] + 1)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
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

int solve()
{
  int maxFlow = dinic();
  vector<pair<int, int>> paths;
  queue<pair<int, pair<int, int>>> q; q.push({target, {maxFlow, 0}});
  while (!q.empty())
  {
    int u = q.front().first, flow = q.front().second.first, d = q.front().second.second; q.pop();
    if (u == source)
    {
      paths.push_back({flow, d});
      continue;
    }
    for (Edge &e: graph[u])
      if (e.flow > 0 && !e.capacity)
      {
        int aux = min(e.flow, flow);
        if (aux == 0) continue;
        q.push({e.to, {aux, d + 1}});
        flow -= aux;
        e.flow -= aux;
      }
  }

  int flow = 0, days = 0;
  for (; flow < a; days ++)
  {
    flow = 0;
    for (auto &p: paths)
      flow += p.first * (days >= p.second ? (days - p.second + 1) : 0);
  }
  return days - 1;
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &a) != EOF && !(!n && !m && !a))
  {
    target = n; vertices = n + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    for (int i = 0, u, v, s; i < m; i ++)
    {
      scanf("%d %d %d", &u, &v, &s);
      addEdge(u, v, s);
    }

    int ans = solve();
    printf("%d\n", ans);
  }
  return(0);
}