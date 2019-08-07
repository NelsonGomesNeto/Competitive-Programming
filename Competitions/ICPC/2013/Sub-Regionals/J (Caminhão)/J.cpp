#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e4, maxLog = 20, inf = 1e9; int n, m, s, lgn;
vector<pair<int, int>> graph[maxN], tree[maxN];
bool visited[maxN];

void prim()
{
  memset(visited, false, sizeof(visited));
  priority_queue<pair<int, pair<int, int>>> pq; pq.push({0, {0, -1}});
  while (!pq.empty())
  {
    int u = pq.top().second.first, prv = pq.top().second.second, w = pq.top().first; pq.pop();
    if (visited[u]) continue;
    visited[u] = true;
    if (prv != -1)
      tree[u].push_back({prv, w}), tree[prv].push_back({u, w});
    for (auto &v: graph[u])
      pq.push({v.second, {v.first, u}});
  }
}

int level[maxN], weight[maxN][maxLog], ancestor[maxN][maxLog];
void dfs(int u = 0, int prv = -1)
{
  for (auto &v: tree[u])
    if (v.first != prv)
    {
      level[v.first] = level[u] + 1;
      ancestor[v.first][0] = u;
      weight[v.first][0] = v.second;
      dfs(v.first, u);
    }
}
void build()
{
  level[0] = ancestor[0][0] = 0, weight[0][0] = inf; dfs();
  for (int i = 1; i < lgn; i ++)
    for (int u = 0; u < n; u ++)
    {
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
      weight[u][i] = min(weight[ancestor[u][i - 1]][i - 1], weight[u][i - 1]);
    }
}
pair<int, int> LCA(int u, int v)
{
  int w = inf;
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
    {
      w = min(w, weight[u][i]);
      u = ancestor[u][i];
    }
  if (u == v) return(make_pair(u, w));
  for (int i = lgn - 1; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
    {
      w = min({w, weight[u][i], weight[v][i]});
      u = ancestor[u][i], v = ancestor[v][i];
    }
  w = min({w, weight[u][0], weight[v][0]});
  return(make_pair(ancestor[u][0], w));
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &s) != EOF && n)
  {
    lgn = ceil(log2(n));
    for (int i = 0; i < n; i ++) graph[i].clear(), tree[i].clear();

    for (int i = 0, u, v, w; i < m; i ++)
    {
      scanf("%d %d %d", &u, &v, &w); u --, v --;
      graph[u].push_back({v, w}), graph[v].push_back({u, w});
    }
    prim();
    build();

    for (int i = 0, u, v; i < s; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      pair<int, int> lca = LCA(u, v);
      printf("%d\n", lca.second);
    }
  }
  return(0);
}