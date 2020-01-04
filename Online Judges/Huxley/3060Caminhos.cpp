#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, inf = 1e7; int n, m;
struct Edge { int to, cost; };
vector<Edge> graph[maxN];

int dist[maxN], prv[maxN];
void dijkstra(int source = 0)
{
  for (int i = 0; i < n; i ++) dist[i] = inf, prv[i] = -1;
  priority_queue<pair<int, int>> pq;
  pq.push({dist[0] = 0, 0});
  while (!pq.empty())
  {
    int u = pq.top().second, d = -pq.top().first; pq.pop();
    if (d > dist[u]) continue;
    for (Edge &e: graph[u])
      if (dist[u] + e.cost < dist[e.to])
      {
        prv[e.to] = u;
        pq.push({-(dist[e.to] = dist[u] + e.cost), e.to});
      }
  }
}

void printPath(int u)
{
  if (prv[u] == -1 || dist[u] == inf)
  {
    printf("Path to vertex %d: -\n", u + 1);
    return;
  }
  stack<int> s;
  for (int now = u; now != 0; now = prv[now])
    s.push(prv[now]);
  printf("Path to vertex %d:", u + 1);
  bool first = true;
  while (!s.empty())
  {
    printf("%s%d", first ? " " : ", ", s.top() + 1);
    first = false, s.pop();
  }
  printf(" and distance %d\n", dist[u]);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
      graph[i].clear();
    for (int i = 0; i < m; i ++)
    {
      int u, v, c; scanf("%d %d %d", &u, &v, &c); u --, v --;
      graph[u].push_back({v, c}), graph[v].push_back({u, c});
    }

    dijkstra();
    for (int i = 0; i < n; i ++)
      printPath(i);
  }
  return 0;
}