#include <bits/stdc++.h>
using namespace std;

const int maxVertices = 1e4, inf = 1e4 + 2; int n, m, vertices;
vector<pair<int, int>> graph[maxVertices];
map<int, int> edgesMap[maxVertices];

int cost[maxVertices]; bool visited[maxVertices];
int dijkstra(int source, int destination)
{
  if (source == destination) return(0);
  memset(visited, false, sizeof(visited)); for (int i = 0; i < n; i ++) cost[i] = inf;
  priority_queue<pair<int, int>> pq; pq.push({0, source}), cost[source] = 0;
  while (!pq.empty())
  {
    int u = pq.top().second; pq.pop();
    if (u == destination) break;
    if (visited[u]) continue; visited[u] = true;
    for (auto v: graph[u])
      if (cost[u] + v.second < cost[v.first])
      {
        cost[v.first] = cost[u] + v.second;
        pq.push({-cost[v.first], v.first});
      }
  }
  return(cost[destination] == inf ? -1 : cost[destination]);
}

int parent[maxVertices];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
bool sameSet(int u, int v)
{
  return(root(u) == root(v));
}
void dsuMerge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
int merge(int u, int v)
{
  if (u != v)
  {
    graph[u][edgesMap[u][v]].second = graph[v][edgesMap[v][u]].second = 0;
    if (!sameSet(u, v)) dsuMerge(u, v), vertices --;
  }
  return(vertices);
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &m); vertices = n;
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v);
    if (u == v) continue;
    edgesMap[u][v] = graph[u].size(), edgesMap[v][u] = graph[v].size();
    graph[u].push_back({v, 1}), graph[v].push_back({u, 1});
  }

  int q; scanf("%d", &q);
  while (q --)
  {
    char op; int u, v; scanf("\n%c %d %d", &op, &u, &v);
    if (op == 'c') printf("%d\n", merge(u, v));
    else printf("%d\n", dijkstra(root(u), root(v)));
    // else printf("%d\n", dijkstra(u, v));
  }
  return(0);
}