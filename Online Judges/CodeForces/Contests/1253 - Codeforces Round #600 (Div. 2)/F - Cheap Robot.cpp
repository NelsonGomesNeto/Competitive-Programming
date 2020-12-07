#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Please make the tutorial for this one
  Lot's of things to be learned here
*/

const int maxN = 1e5, maxM = 3e5, maxLog = 20; int n, m, k, q;
struct Edge
{
  int u, v; lli w;
  bool operator<(const Edge &other) const { return w < other.w; }
  bool operator>(const Edge &other) const { return w > other.w; }
  void print() { printf("%d %d %lld\n", u, v, w); }
};

vector<Edge> graph[maxN];
int closestCentral[maxN]; lli closestCentralDistance[maxN];
void dijkstra()
{
  memset(closestCentral, -1, sizeof(closestCentral));
  priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // {central, current, w}
  for (int i = 0; i <= k; i ++)
    pq.push({i, i, 0});
  while (!pq.empty())
  {
    Edge e = pq.top(); pq.pop();
    if (closestCentral[e.v] != -1) continue;
    closestCentral[e.v] = e.u, closestCentralDistance[e.v] = e.w;
    for (Edge &ne: graph[e.v])
      pq.push({e.u, ne.v, e.w + ne.w});
  }
}

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

vector<Edge> edges;
vector<Edge> tree[maxN];
void kruskal()
{
  memset(parent, -1, sizeof(parent));
  sort(edges.begin(), edges.end());
  for (Edge &e: edges)
    if (root(e.u) != root(e.v))
    {
      merge(e.u, e.v);
      tree[e.u].push_back({e.u, e.v, e.w});
      tree[e.v].push_back({e.v, e.u, e.w});
    }
}

int ancestor[maxN][maxLog], level[maxN]; lli weight[maxN][maxLog];
void dfs(int u, int prv = -1)
{
  for (Edge &e: tree[u])
    if (e.v != prv)
    {
      ancestor[e.v][0] = u, level[e.v] = level[e.u] + 1, weight[e.v][0] = e.w;
      dfs(e.v, u);
    }
}
void buildLCA()
{
  ancestor[0][0] = level[0] = weight[0][0] = 0;
  dfs(0);

  for (int i = 1; i < maxLog; i ++)
    for (int u = 0; u < n; u ++)
    {
      weight[u][i] = max(weight[u][i - 1], weight[ancestor[u][i - 1]][i - 1]);
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
    }
}
pair<int, lli> LCA(int u, int v)
{
  pair<int, lli> ans = {0, 0};
  if (level[v] > level[u]) swap(u, v);

  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
    {
      ans.second = max(ans.second, weight[u][i]);
      u = ancestor[u][i];
    }

  if (u == v)
    return ans;

  for (int i = maxLog - 1; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
    {
      ans.second = max({ans.second, weight[u][i], weight[v][i]});
      u = ancestor[u][i], v = ancestor[v][i];
    }
  ans.first = ancestor[u][0];
  ans.second = max({ans.second, weight[u][0], weight[v][0]});

  return ans;
}

int main()
{
  while (scanf("%d %d %d %d", &n, &m, &k, &q) != EOF)
  {
    edges.clear();
    for (int i = 0; i < n; i ++)
      graph[i].clear(), tree[i].clear();
    k --;

    for (int i = 0; i < m; i ++)
    {
      int u, v; lli w;
      scanf("%d %d %lld", &u, &v, &w); u --, v --;
      graph[u].push_back({u, v, w}), graph[v].push_back({v, u, w});
    }
    dijkstra();

    for (int u = 0; u < n; u ++)
      for (Edge &e: graph[u])
        if (closestCentral[u] != closestCentral[e.v])
          edges.push_back({closestCentral[u], closestCentral[e.v], closestCentralDistance[u] + e.w + closestCentralDistance[e.v]});

    kruskal();

    buildLCA();

    for (int qq = 0; qq < q; qq ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      pair<int, lli> lca = LCA(u, v);
      DEBUG printf("(%d, %d) = %d %lld\n", u + 1, v + 1, lca.first + 1, lca.second);
      else printf("%lld\n", lca.second);
    }
  }
  return 0;
}
