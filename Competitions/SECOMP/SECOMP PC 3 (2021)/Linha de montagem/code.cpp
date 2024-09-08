#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxV = 2 + 2e5 + 2e5 - 2 + 2; int n, vertices;
const lli inf = LONG_LONG_MAX;
lli e[2], x[2];
lli a[2][maxN];
lli t[2][maxN - 1];
vector<lli> nodes;
vector<int> graph[maxV];
lli dist[maxV];
int prv[maxV];

struct Node
{
  int u; lli d;
  bool operator<(const Node &other) const
  {
    return d > other.d;
  }
};
lli dijkstra()
{
  for (int i = 0; i < vertices; i++) dist[i] = inf, prv[i] = -1;
  priority_queue<Node> pq;
  pq.push(Node{0, dist[0] = nodes[0]});
  pq.push(Node{1, dist[1] = nodes[1]});
  while (!pq.empty())
  {
    Node curr = pq.top(); pq.pop();
    if (curr.d > dist[curr.u]) continue;

    for (int v: graph[curr.u])
      if (curr.d + nodes[v] < dist[v])
      {
        prv[v] = curr.u;
        pq.push(Node{v, dist[v] = curr.d + nodes[v]});
      }
  }

  return min(dist[vertices - 1], dist[vertices - 2]);
}

int main()
{
  int tests; scanf("%d", &tests);
  for (int test = 0; test < tests; test++)
  {
    scanf("%d", &n);
    assert(n <= maxN);
    vertices = 2 + 2*n + 2*n - 2 + 2;
    assert(vertices <= maxV);
    for (int i = 0; i < vertices; i++) graph[i].clear();

    nodes.clear();
    for (int i = 0; i < 2; i++)
    {
      scanf("%lld", &e[i]);
      nodes.push_back(e[i]);
      graph[i].push_back(2 + i*n);
    }

    for (int i = 0; i < 2; i++)
      for (int j = 0; j < n; j++)
      {
        scanf("%lld", &a[i][j]);
        nodes.push_back(a[i][j]);
        if (j + 1 < n)
        {
          graph[2 + i*n + j].push_back(2 + i*n + j + 1);
          graph[2 + i*n + j].push_back(2 + 2*n + i*(n - 1) + j);
        }
      }
    graph[2 + n - 1].push_back(vertices - 2);
    graph[2 + n + n - 1].push_back(vertices - 1);

    for (int i = 0; i < 2; i++)
      for (int j = 0; j < n - 1; j++)
      {
        scanf("%lld", &t[i][j]);
        nodes.push_back(t[i][j]);
        graph[2 + 2*n + i*(n - 1) + j].push_back(2 + (1 - i)*n + j + 1);
      }
    for (int i = 0; i < 2; i++)
    {
      scanf("%lld", &x[i]);
      nodes.push_back(x[i]);
    }

    assert(nodes.size() == vertices);

    lli ans = dijkstra();
    printf("%lld\n", ans);
  }
  return 0;
}
