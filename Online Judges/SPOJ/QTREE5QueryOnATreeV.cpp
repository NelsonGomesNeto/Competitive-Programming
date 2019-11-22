#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxLog = 20; int n, q;
vector<int> tree[maxN];
void addEdge(vector<int> g[], int u, int v)
{
  g[u].push_back(v), g[v].push_back(u);
}
bool white[maxN];

vector<int> centroidTree[maxN];
bool inCentroidTree[maxN]; int subtree[maxN], centroidRoot, centroidLevel[maxN];
int getSubtreeSize(int u, int prv = -1)
{
  subtree[u] = 1;
  for (int v: tree[u])
    if (v != prv && !inCentroidTree[v])
      subtree[u] += getSubtreeSize(v, u);
  return subtree[u];
}
int getCentroid(int u, int nodes, int prv = -1)
{
  bool validCentroid = nodes - subtree[u] <= (nodes >> 1);
  int heaviestChild = -1;
  for (int v: tree[u])
    if (v != prv && !inCentroidTree[v])
    {
      if (subtree[v] > (nodes >> 1))
        validCentroid = false;
      if (heaviestChild == -1 || (subtree[v] > subtree[heaviestChild]))
        heaviestChild = v;
    }
  if (validCentroid)
    return u;
  return getCentroid(heaviestChild, nodes, u);
}
int centroidDecomposition(int u = 0, int prv = -1)
{
  int centroid = getCentroid(u, getSubtreeSize(u));
  inCentroidTree[centroid] = true;
  centroidLevel[centroid] = prv == -1 ? 0 : centroidLevel[prv] + 1;
  for (int v: tree[centroid])
    if (v != prv && !inCentroidTree[v])
    {
      int centroidChild = centroidDecomposition(v, centroid);
      addEdge(centroidTree, centroid, centroidChild);
    }
  return centroid;
}

int ancestor[maxN][maxLog], level[maxN];
void dfs(int u = 0, int prv = -1)
{
  for (int v: tree[u])
    if (v != prv)
    {
      ancestor[v][0] = u, level[v] = level[u] + 1;
      dfs(v, u);
    }
}
void buildLCA()
{
  ancestor[0][0] = level[0] = 0;
  dfs(0);
  for (int i = 1; i < maxLog; i ++)
    for (int u = 0; u < n; u ++)
      ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
}
int LCA(int u, int v)
{
  if (level[v] > level[u]) swap(u, v);
  for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, i ++)
    if (diff & 1)
      u = ancestor[u][i];
  if (u == v)
    return u;
  for (int i = maxLog - 1; ancestor[u][0] != ancestor[v][0]; i --)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return ancestor[u][0];
}
int dist(int u, int v)
{
  int lca = LCA(u, v);
  return level[u] + level[v] - 2*level[lca];
}

multiset<int> closest[maxN]; // remember that multiset erase erases all occurences
void update(int x, int u, bool toAdd)
{
  if (toAdd) closest[u].insert(dist(x, u));
  else closest[u].erase(closest[u].find(dist(x, u)));
  for (int v: centroidTree[u])
    if (centroidLevel[v] < centroidLevel[u])
      update(x, v, toAdd);
}
int query(int x, int u)
{
  int ans = *closest[u].begin() + dist(x, u);
  for (int v: centroidTree[u])
    if (centroidLevel[v] < centroidLevel[u])
      ans = min(ans, query(x, v));
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(white, false, sizeof(white)), memset(inCentroidTree, false, sizeof(inCentroidTree));
    for (int i = 0; i < n; i ++)
    {
      tree[i].clear(), centroidTree[i].clear(), closest[i].clear();
      closest[i].insert(maxN);
    }

    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      addEdge(tree, u, v);
    }
    centroidRoot = centroidDecomposition();
    buildLCA();

    scanf("%d", &q);
    while (q --)
    {
      int t, u; scanf("%d %d", &t, &u); u --;
      if (t == 0) update(u, u, white[u] = !white[u]);
      else
      {
        int ans = query(u, u);
        printf("%d\n", ans >= maxN ? -1 : ans);
      }
    }
  }
  return 0;
}