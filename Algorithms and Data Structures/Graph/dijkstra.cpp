#include <bits/stdc++.h>
using namespace std;
const int maxVertices = 1e3, inf = 1e9;

struct Edge
{
  int from, to, d;
};
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int c, bool undirected = false)
{
  graph[u].push_back(Edge{u, v, c});
  graph[v].push_back(Edge{v, u, c});
}

struct State
{
  int u, d;
  bool operator<(const State &other) const { return d > other.d; }
};

int dist[maxVertices], prv[maxVertices];
void dijkstra(int source)
{
  for (int i = 0; i < maxVertices; i ++) dist[i] = inf;
  priority_queue<State> pq;
  pq.push(State{source, dist[source] = 0});

  while (!pq.empty())
  {
    int u = pq.top().u, d = pq.top().d; pq.pop();
    if (d > dist[u]) continue;

    for (auto &e: graph[u])
      if (d + e.d < dist[e.to])
      {
        dist[e.to] = d + e.d, prv[e.to] = u;
        pq.push(State{e.to, dist[e.to]});
      }
  }
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int u, v, c;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &c); u --, v --;
    addEdge(u, v, c, true);
  }

  dijkstra(0);

  printf("%d\n", dist[n - 1]);
  for (int i = 0; i < n; i ++) printf("%3d%c", i, i < n - 1 ? ' ' : '\n');
  for (int i = 0; i < n; i ++) printf("%3d%c", dist[i], i < n - 1 ? ' ' : '\n');
  for (int i = 0; i < n; i ++) printf("%3d%c", prv[i], i < n - 1 ? ' ' : '\n');

  return 0;
}
