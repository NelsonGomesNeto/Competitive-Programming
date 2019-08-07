#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const lli inf = 1e18;
const int maxN = 1e4, maxM = 1e5; int n, m;
struct Edge
{
  int city; lli length, cost; int prevCity;
  bool operator<(const Edge &a) const { return(length > a.length || (length == a.length && cost > a.cost)); }
};
vector<Edge> graph[maxN], tree[maxN];

lli dist[maxN], cost[maxN], treeCost;
void dijkstra()
{
  for (int i = 0; i < n; i ++) dist[i] = cost[i] = inf;
  priority_queue<Edge> pq;
  pq.push({0, 0, 0, -1}); dist[0] = cost[0] = 0;
  while (!pq.empty())
  {
    Edge u = pq.top(); pq.pop();
    if (u.length > dist[u.city] || (u.length == dist[u.city] && u.cost > cost[u.city])) continue;
    if (u.prevCity != -1) tree[u.prevCity].push_back({u.city, u.length, u.cost});
    treeCost += u.cost;
    for (auto v: graph[u.city])
      if (dist[u.city] + v.length < dist[v.city] || (dist[u.city] + v.length == dist[v.city] && v.cost < cost[v.city]))
      {
        dist[v.city] = dist[u.city] + v.length, cost[v.city] = v.cost;
        pq.push({v.city, dist[v.city], cost[v.city], u.city});
      }
  }
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v, l, c; i < m; i ++)
  {
    scanf("%d %d %d %d", &u, &v, &l, &c); u --, v --;
    graph[u].push_back({v, l, c}), graph[v].push_back({u, l, c});
  }

  dijkstra();
  printf("%lld\n", treeCost);

  DEBUG for (int i = 0; i < n; i ++)
  {
    printf("%d:", i + 1);
    for (auto e: tree[i]) printf(" (%d %lld %lld)", e.city + 1, e.length, e.cost);
    printf("\n");
  }

  return(0);
}