#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  No lugar de [V][(min, max)]
  Fazer [V][(hadMin, hadMax)]
*/

const int maxN = 2e5; int n, m;
struct Edge
{
  int from, to; lli weight;
};
vector<Edge> graph[maxN];
void addEdge(int u, int v, lli w)
{
  graph[u].push_back({u, v, w});
  graph[v].push_back({v, u, w});
}

lli dist[maxN][2][2];
const lli inf = 1e16;
struct Node
{
  int u; lli sum, maximum, minimum; bool hadMaximum, hadMinimum;
  lli cost() const { return sum - hadMaximum*maximum + hadMinimum*minimum; }
  bool operator<(const Node &other) const
  {
    return cost() > other.cost();
  }
};
void dijkstra()
{
  for (int i = 0; i < n; i++) 
    dist[i][0][0] = dist[i][0][1] = dist[i][1][0] = dist[i][1][1] = inf;

  priority_queue<Node> pq;
  pq.push({0, dist[0][0][0] = 0, 0, 0, false, false});
  while (!pq.empty())
  {
    Node now = pq.top(); pq.pop();
    if (now.cost() > dist[now.u][now.hadMaximum][now.hadMinimum]) continue;

    for (Edge &e: graph[now.u])
    {
      Node newNode = now;
      if (newNode.maximum != 0 && now.hadMaximum && e.weight > now.maximum)
        continue;
      if (newNode.minimum != 0 && now.hadMinimum && e.weight < now.minimum)
        continue;

      if (newNode.maximum == 0 || e.weight > now.maximum)
        newNode.maximum = e.weight;
      if (newNode.minimum == 0 || e.weight < now.minimum)
        newNode.minimum = e.weight;

      newNode.sum += e.weight;
      newNode.u = e.to;

      for (int mx = now.hadMaximum; mx <= 1; mx++)
        for (int mn = now.hadMinimum; mn <= 1; mn++)
        {
          newNode.hadMaximum = mx;
          newNode.hadMinimum = mn;
          if (newNode.cost() < dist[newNode.u][newNode.hadMaximum][newNode.hadMinimum])
          {
            dist[newNode.u][newNode.hadMaximum][newNode.hadMinimum] = newNode.cost();
            pq.push(newNode);
          }
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
      int u, v; lli w; scanf("%d %d %lld", &u, &v, &w); u--, v--;
      addEdge(u, v, w);
    }

    dijkstra();
    for (int i = 1; i < n; i++)
    {
      lli v = dist[i][1][1];
      printf("%lld%c", v, i < n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}