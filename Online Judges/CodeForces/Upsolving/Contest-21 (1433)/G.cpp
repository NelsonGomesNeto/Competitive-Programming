#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m, k;
const int inf = 1e9;
struct Edge
{
  int to, from, c;
};
vector<Edge> graph[maxN], edges;
void addEdge(int u, int v, int w)
{
  graph[u].push_back(Edge{v, u, w});
  graph[v].push_back(Edge{u, v, w});
  edges.push_back(Edge{u, v, w});
}

struct Node
{
  int u, d;
  bool operator<(const Node &other) const { return d > other.d; }
};
int dist[maxN][maxN];
void dijkstra(int u)
{
  for (int i = 0; i < n; i++) dist[u][i] = inf;
  priority_queue<Node> pq;
  pq.push(Node{u, dist[u][u] = 0});
  while (!pq.empty())
  {
    Node now = pq.top(); pq.pop();
    if (now.d > dist[u][now.u]) continue;
    for (Edge &e: graph[now.u])
      if (now.d + e.c < dist[u][e.to])
        pq.push(Node{e.to, dist[u][e.to] = now.d + e.c});
  }
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    edges.clear();
    for (int i = 0; i < n; i++) graph[i].clear();

    for (int i = 0; i < m; i++)
    {
      int u, v, w; scanf("%d %d %d", &u, &v, &w); u--, v--;
      addEdge(u, v, w);
    }

    for (int i = 0; i < n; i++)
      dijkstra(i);

    vector<pair<int, int>> routes;
    for (int i = 0; i < k; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      routes.push_back({u, v});
    }
    int ans = inf;

    for (int i = 0; i < m; i++)
    {
      int total = 0;
      for (int j = 0; j < k; j++)
      {
        int u = routes[j].first, v = routes[j].second;
        total += min({
          dist[u][v],
          dist[u][edges[i].from] + dist[edges[i].to][v],
          dist[u][edges[i].to] + dist[edges[i].from][v]
        });
      }
      ans = min(ans, total);
    }

    printf("%d\n", ans);
  }
  return 0;
}