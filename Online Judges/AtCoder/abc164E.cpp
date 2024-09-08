#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, m, s;
const lli inf = LONG_LONG_MAX;
const int maxS = 2501;
struct Edge
{
  int to, a; lli b;
};
vector<Edge> graph[maxN];
int c[maxN]; lli d[maxN];

struct Node
{
  lli d; int i, silver;
  bool operator<(const Node &other) const { return d > other.d; }
};
lli dist[maxN][maxS + 1];
void dijkstra(int source = 0)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j <= maxS; j++)
      dist[i][j] = inf;
  queue<Node> pq; pq.push({dist[source][s] = 0, source, s});
  while (!pq.empty())
  {
    Node u = pq.front(); pq.pop();
    if (u.d > dist[u.i][u.silver]) continue;
    for (Edge &e: graph[u.i])
      for (int j = 0; j < maxS; j++)
        if (u.silver + c[u.i]*j >= e.a)
        {
          lli newDist = dist[u.i][u.silver] + e.b + d[u.i]*j;
          int newSilver = min(maxS, u.silver + c[u.i]*j - e.a);
          if (newDist < dist[e.to][newSilver])
            pq.push({dist[e.to][newSilver] = newDist, e.to, newSilver});
          if (u.silver + c[u.i]*j - e.a > maxS)
            break;
        }
  }
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &s) != EOF)
  {
    for (int i = 0; i < n; i++)
      graph[i].clear();
    s = min(s, maxS);
    for (int i = 0; i < m; i++)
    {
      int u, v, a; lli b;
      scanf("%d %d %d %lld", &u, &v, &a, &b); u--, v--;
      graph[u].push_back({v, a, b});
      graph[v].push_back({u, a, b});
    }
    for (int i = 0; i < n; i++)
      scanf("%d %lld", &c[i], &d[i]);

    dijkstra();
    for (int i = 1; i < n; i++)
      printf("%lld\n", *min_element(dist[i], dist[i]+maxS));
  }
  return 0;
}