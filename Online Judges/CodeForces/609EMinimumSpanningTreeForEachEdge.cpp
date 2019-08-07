#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5, maxLog = ceil(log2(2e5)) + 1; int n, m, logn;
vector<pair<int, lli>> graph[maxN], tree[maxN]; lli edge[maxN][3];
lli prim()
{
  bool visited[n]; memset(visited, false, sizeof(visited)); visited[0] = true;
  priority_queue<pair<lli, pair<int, int>>> pq; // {-cost, {u, prev}}
  for (auto v: graph[0]) pq.push({-v.second, {v.first, 0}});
  lli cost = 0;
  while (!pq.empty())
  {
    int u = pq.top().second.first, prev = pq.top().second.second, c = -pq.top().first; pq.pop();
    if (visited[u]) continue;
    tree[u].push_back({prev, c}); tree[prev].push_back({u, c}); cost += c;
    visited[u] = true;
    for (auto v: graph[u]) pq.push({-v.second, {v.first, u}});
  }
  return(cost);
}

int level[maxN], ancestor[maxN][maxLog]; lli weight[maxN][maxLog];
void dfs(int u, int prev)
{
  for (auto v: tree[u])
    if (v.first != prev)
    {
      level[v.first] = level[u] + 1, ancestor[v.first][0] = u, weight[v.first][0] = v.second;
      dfs(v.first, u);
    }
}
void build()
{
  level[0] = ancestor[0][0] = weight[0][0] = 0; dfs(0, -1);
  for (int i = 1; i <= logn; i ++)
    for (int u = 0; u < n; u ++)
    {
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
      weight[u][i] = max(weight[u][i - 1], weight[ancestor[u][i - 1]][i - 1]);
    }
}
pair<int, lli> LCA(int u, int v)
{
  lli heaviestEdge = 0;
  if (level[v] > level[u]) swap(u, v);

  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
    {
      heaviestEdge = max(heaviestEdge, weight[u][i]);
      u = ancestor[u][i];
    }

  if (u == v) return(make_pair(u, heaviestEdge));

  for (int i = logn; i >= 0; i --)
    if (ancestor[u][i] != ancestor[v][i])
    {
      heaviestEdge = max(max(heaviestEdge, weight[u][i]), weight[v][i]);
      u = ancestor[u][i], v = ancestor[v][i];
    }
  heaviestEdge = max(max(heaviestEdge, weight[u][0]), weight[v][0]);

  return(make_pair(ancestor[u][0], heaviestEdge));
}

int main()
{
  scanf("%d %d", &n, &m); logn = ceil(log2(n));
  int u, v; lli c;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d %lld", &u, &v, &c); u --, v --;
    graph[u].push_back({v, c}); graph[v].push_back({u, c});
    edge[i][0] = u, edge[i][1] = v, edge[i][2] = c;
  }
  lli mstCost = prim();
  build();

  for (int i = 0; i < m; i ++)
    printf("%lld\n", mstCost + edge[i][2] - LCA(edge[i][0], edge[i][1]).second);

  return(0);
}
