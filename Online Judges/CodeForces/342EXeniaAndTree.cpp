#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxLog = 20; int n, q;
vector<int> tree[maxN];

vector<int> centroidTree[maxN];
bool inCentroidTree[maxN]; int centroidRoot;
int centroidLevel[maxN], subtree[maxN];
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
      centroidTree[centroid].push_back(centroidChild), centroidTree[centroidChild].push_back(centroid);
    }
  return centroid;
}

int ancestor[maxN][maxLog], level[maxN];
void dfs(int u, int prv = -1)
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
  level[0] = ancestor[0][0] = 0;
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
  if (u == v) return u;
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

int closest[maxN];
void update(int x, int u)
{
  closest[u] = min(closest[u], dist(x, u));
  for (int v: centroidTree[u])
    if (centroidLevel[v] < centroidLevel[u])
      update(x, v);
}
int query(int x, int u)
{
  int ans = closest[u] + dist(x, u);
  for (int v: centroidTree[u])
  {
    DEBUG printf("\t%d %d - %d\n", x + 1, u + 1, v + 1);
    if (centroidLevel[v] < centroidLevel[u])
      ans = min(ans, query(x, v));
  }
  return ans;
}

void printSpaces(int spaces) { while (spaces --) printf("   "); }
void printTree(vector<int> t[], int u, int prv = -1, int depth = 0)
{
  printSpaces(depth);
  printf("%d\n", u + 1);
  for (int v: t[u])
    if (v != prv)
      printTree(t, v, u, depth + 1);
}

int main()
{
  while (scanf("%d %d", &n, &q) != EOF)
  {
    memset(inCentroidTree, false, sizeof(inCentroidTree));
    memset(centroidLevel, 0, sizeof(centroidLevel));
    for (int i = 0; i < n; i ++)
      tree[i].clear(), centroidTree[i].clear(), closest[i] = maxN;

    for (int i = 0; i < n - 1; i ++)
      tree[i].push_back(i + 1), tree[i + 1].push_back(i);
    centroidRoot = centroidDecomposition();
    printTree(centroidTree, centroidRoot);

    for (int i = 0; i < n; i ++)
      tree[i].clear();
    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      tree[u].push_back(v), tree[v].push_back(u);
    }
    buildLCA();

    update(0, 0);
    for (int qq = 0; qq < q; qq ++)
    {
      int t, v; scanf("%d %d", &t, &v); v --;
      if (t == 1) update(v, v);
      else printf("%d\n", query(v, v));
    }
  }
  return 0;
}