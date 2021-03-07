#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
(x + y)^2 = x^2 + 2*x*y + y^2
*/

const int maxN = 1e5, maxW = 51; int n, m;
const int inf = INT_MAX;
vector<pair<int, int>> graph[maxN];

int dist[maxN][2][maxW];
struct Node
{
  int u, parity, prvW, d;
  // bool operator<(const Node &other) const { return parity < other.parity || (parity == other.parity && prvW > other.prvW) || (parity == other.parity && prvW == other.prvW && d > other.d); };
  bool operator<(const Node &other) const { return d > other.d; };
};
void dijkstra()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < maxW; j++)
      dist[i][0][j] = dist[i][1][j] = inf;
  priority_queue<Node> pq;
  pq.push(Node{0, 1, 0, dist[0][1][0] = 0});

  while (!pq.empty())
  {
    Node now = pq.top(); pq.pop();
    if (now.d > dist[now.u][now.parity][now.prvW]) continue;

    for (auto &[v, w]: graph[now.u])
    {
      Node newNode = Node{v, !now.parity, w, now.d + (now.parity ? w*w : 2*w*now.prvW + w*w)};
      if (newNode.d < dist[newNode.u][newNode.parity][newNode.prvW])
      {
        dist[newNode.u][newNode.parity][newNode.prvW] = newNode.d;
        pq.push(newNode);
      }
    }
  }
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
      graph[i].clear();

    for (int i = 0; i < m; i++)
    {
      int u, v, w; scanf("%d %d %d", &u, &v, &w); u--, v--;
      graph[u].push_back({v, w});
      graph[v].push_back({u, w});
    }

    dijkstra();
    for (int i = 0; i < n; i++)
    {
      int minimum = inf;
      for (int j = 0; j < maxW; j++)
        minimum = min(minimum, dist[i][1][j]);
      if (minimum == inf)
        minimum = -1;
      printf("%d%c", minimum, i < n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
