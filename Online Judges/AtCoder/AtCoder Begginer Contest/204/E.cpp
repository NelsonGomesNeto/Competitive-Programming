#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
const lli inf = LONG_LONG_MAX;
struct Edge
{
  int to; lli c, d;
};
vector<Edge> graph[maxN];

struct Node
{
  int u; lli t;
  bool operator<(const Node &other) const { return t > other.t; }
};
lli bestTime(lli t, lli c, lli d)
{
  return t + c + d / (t + 1);
}
lli dist[maxN];
lli dijkstra(lli startTime)
{
  for (int i = 0; i < n; i++) dist[i] = inf;
  priority_queue<Node> pq;
  pq.push(Node{0, dist[0] = startTime});
  while (!pq.empty())
  {
    int u = pq.top().u; lli t = pq.top().t; pq.pop();
    if (t > dist[u]) continue;

    for (Edge &e: graph[u])
    {
      lli newT = bestTime(t, e.c, e.d);
      if (newT < dist[e.to])
        pq.push(Node{e.to, dist[e.to] = newT});
    }
  }
  return dist[n - 1];
}

struct Node2
{
  int u; double t;
  bool operator<(const Node2 &other) const { return t > other.t; }
};
double bestTime2(double t, lli c, lli d)
{
  return t + c + (double)d / (t + 1);
}
double dist2[maxN];
double dijkstra2(double startTime)
{
  for (int i = 0; i < n; i++) dist2[i] = inf;
  priority_queue<Node2> pq;
  pq.push(Node2{0, dist2[0] = startTime});
  while (!pq.empty())
  {
    int u = pq.top().u; double t = pq.top().t; pq.pop();
    if (t > dist2[u]) continue;

    for (Edge &e: graph[u])
    {
      double newT = bestTime2(t, e.c, e.d);
      if (newT < dist2[e.to])
        pq.push(Node2{e.to, dist2[e.to] = newT});
    }
  }
  return dist2[n - 1];
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) graph[i].clear();
    for (int i = 0; i < m; i++)
    {
      int u, v; lli c, d; scanf("%d %d %lld %lld", &u, &v, &c, &d); u--, v--;
      graph[u].push_back(Edge{v, c, d});
      graph[v].push_back(Edge{u, c, d});
    }

    lli ans = dijkstra(0);
    if (ans == inf) printf("-1\n");
    else
    {
      double lo = 0, hi = 1e9;
      while (hi - lo >= 5)
      {
        double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
        double elo = dijkstra2(midlo), ehi = dijkstra2(midhi);
        if (abs(elo - ehi) <= 1e-5) hi = midhi;
        else if (elo < ehi) hi = midhi;
        else lo = midlo;
      }
      for (lli i = max(0.0, lo - 1); i <= hi + 1; i++)
        ans = min(ans, dijkstra(i));

      printf("%lld\n", ans);
    }
  }
  return 0;
}
