#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, inf = 1e9; int n, m, c, r;
vector<pair<int, int>> graph[maxN];
vector<pair<int, pair<int, int>>> edges;

int parent[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
int kruskal()
{
  int mstCost = 0;
  for (auto &e: edges)
    if (root(e.second.first) != root(e.second.second))
    {
      merge(e.second.first, e.second.second);
      mstCost += e.first * c;
    }
  return mstCost;
}

int dist[maxN];
int dijkstra()
{
  for (int i = 0; i < n; i ++) dist[i] = inf;
  priority_queue<pair<int, int>> pq;
  pq.push({-(dist[0] = 0), 0});
  while (!pq.empty())
  {
    int u = pq.top().second, d = -pq.top().first; pq.pop();
    if (d > dist[u]) continue;
    for (auto &v: graph[u])
      if (dist[u] + r < dist[v.first])
        pq.push({-(dist[v.first] = dist[u] + r), v.first});
  }
  int dijkstraCost = 0;
  for (int i = 0; i < n; i ++) dijkstraCost += dist[i];
  return dijkstraCost;
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &m);
  scanf("%d %d", &c, &r);
  for (int i = 0; i < m; i ++)
  {
    int u, v, w; scanf("%d %d %d", &u, &v, &w);
    graph[u].push_back({v, w}), graph[v].push_back({u, w});
    edges.push_back({w, {u, v}});
  }
  sort(edges.begin(), edges.end());

  int mstCost = kruskal(), dijkstraCost = dijkstra();
  printf("%d %d\n", mstCost, dijkstraCost);

  return(0);
}