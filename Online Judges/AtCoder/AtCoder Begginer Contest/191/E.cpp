#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, m;
const int inf = 1e9;
vector<pair<int, int>> graph[maxN];

struct Node
{
  int u, d, done;
  bool operator<(const Node &other) const { return d > other.d; }
};
int dist[2][maxN];
int dijkstra(int origin)
{
  for (int i = 0; i < n; i++)
    dist[0][i] = dist[1][i] = inf;
  priority_queue<Node> pq;
  pq.push({origin, dist[0][origin] = 0, 0});
  while (!pq.empty())
  {
    Node now = pq.top(); pq.pop();
    if (now.d > dist[now.done][now.u]) continue;

    for (auto &[v, c]: graph[now.u])
    {
      int newDist = c + dist[now.done][now.u];
      if (newDist < dist[1][v])
        pq.push(Node{v, dist[1][v] = newDist, 1});
    }
  }
  return dist[1][origin] == inf ? -1 : dist[1][origin];
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
      graph[i].clear();

    for (int i = 0; i < m; i++)
    {
      int u, v, c; scanf("%d %d %d", &u, &v, &c); u--, v--;
      graph[u].push_back({v, c});
    }

    for (int i = 0; i < n; i++)
      printf("%d\n", dijkstra(i));
  }
  return 0;
}