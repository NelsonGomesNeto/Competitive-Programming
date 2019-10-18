#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3, maxX = 2e5 + 1; int n;
vector<int> primes;
bool notPrime[maxX];

// source (0) -> odd numbers (1 : oddSize) -[if sum is prime]> even numbers (1 + oddSize : oddSize + evenSize) -> sink (1 + oddSize + evenSize)
const int maxV = 2e3 + 2, inf = 1e9;
vector<int> odd, even;
int source, sink, vertices, level[maxV], ptr[maxV];
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
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
  // MVC = {right visited (starting from unmatched left)} + {left unvisited}
  memset(visited, false, sizeof(visited));
  vector<int> ans;
  queue<int> q;
  // unmatched left
  for (int i = 1; i <= odd.size(); i ++)
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
      // left to right has flow if is unmatched
      // right to left hasn't flow if is matched
      if (e.to != source && e.to != sink && e.flow)
        q.push(e.to);
  }
  // right visited
  for (int i = 1 + odd.size(); i <= odd.size() + even.size(); i ++)
    if (visited[i])
      ans.push_back(i);
  // left unvisited
  for (int i = 1; i <= odd.size(); i ++)
    if (!visited[i])
      ans.push_back(i);
  return ans;
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i < maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] < maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    int a; scanf("%d", &a);
    if (a & 1) odd.push_back(a);
    else even.push_back(a);
  }
  sink = 1 + odd.size() + even.size(); vertices = sink + 1;

  for (int i = 0; i < odd.size(); i ++)
    addEdge(source, 1 + i, 1);
  for (int i = 0; i < odd.size(); i ++)
    for (int j = 0; j < even.size(); j ++)
      if (!notPrime[odd[i] + even[j]])
        addEdge(1 + i, 1 + odd.size() + j, 1);
  for (int i = 0; i < even.size(); i ++)
    addEdge(1 + odd.size() + i, sink, 1);

  int maxFlow = dinic();
  printf("%d\n", maxFlow);
  vector<int> mvc = minimumVertexCover();
  for (int i = 0; i < mvc.size(); i ++)
    printf("%d%c", mvc[i] <= odd.size() ? odd[mvc[i] - 1] : even[mvc[i] - odd.size() - 1], i < mvc.size() - 1 ? ' ' : '\n');

  return 0;
}