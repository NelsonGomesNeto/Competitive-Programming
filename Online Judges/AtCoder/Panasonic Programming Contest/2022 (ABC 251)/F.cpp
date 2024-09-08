#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct DSU
{
  int size;
  vector<int> parents;
  DSU() { parents.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init() { parents.resize(size, -1); }
  int root(int u) { return parents[u] < 0 ? u : parents[u] = root(parents[u]); }
  void merge(int u, int v)
  {
    u = root(u), v = root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int setSize(int u) { return -parents[root(u)]; }
  bool sameSet(int u, int v) { return root(u) == root(v); }
};
DSU dsu1, dsu2;

struct LCA
{
  vector<vector<int>> tree;
  vector<int> level, logMemo;
  vector<vector<int>> ancestor;
  int n, logn;
  LCA() {}
  LCA(int n) : n(n), logn(ceil(log2(n)))
  {
    logMemo.clear(); logMemo.resize(n + 1);
    logMemo[1] = 0; for (int i = 2; i <= n; ++i) logMemo[i] = logMemo[i >> 1] + 1;

    tree.clear(); tree.resize(n);
    level.clear(); level.resize(n, 0);
    ancestor.clear(); ancestor.resize(n, vector<int>(logn, 0));
  }

  void printBinary(int num)
  {
    if (!num) return;
    printBinary(num >> 1);
    printf("%d", num & 1);
  }
  void printMatrix()
  {
    printf("   |"); for (int i = 0; i < logn; ++i) printf("%3d%c", i, i < logn - 1 ? '|' : '\n');
    for (int i = 0; i < n; ++i)
    {
      printf("%3d|", i);
      for (int j = 0; j < logn; ++j)
        printf("%3d%c", ancestor[i][j], j < logn - 1 ? '|' : '\n');
    }
  }
  void printSpacing(int s)
  {
    while (s --) printf("   ");
  }

  void addEdge(int u, int v)
  {
    tree[u].push_back(v), tree[v].push_back(u);
  }
  void dfs(int u, int prv = -1)
  {
    DEBUG { printSpacing(level[u]); printf("%3d\n", u); }
    for (int v: tree[u])
      if (v != prv)
      {
        level[v] = level[u] + 1, ancestor[v][0] = u;
        dfs(v, u);
      }
  }
  void build()
  {
    level[0] = ancestor[0][0] = 0; dfs(0);
    for (int i = 1; i < logn; ++i)
      for (int u = 0; u < n; ++u)
      {
        ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
        // If you want to add something about the path, like weight:
        // weight[u][i] = combination of weight[u][i - 1] and weight[ancestor[u][i - 1]][i - 1]
      }
  }
  int lca(int u, int v)
  {
    if (level[v] > level[u]) swap(u, v);

    DEBUG {
      printf("(%d - %d) = %d ", level[u], level[v], level[u] - level[v]);
      printBinary(level[u] - level[v]);
      printf("\n");
    }
    for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, ++i)
      if (diff & 1) u = ancestor[u][i];

    if (u == v) return(u);

    // (i = logn - 1; i >= 0; i --) works as well
    for (int i = logMemo[level[u] - 1]; ancestor[u][0] != ancestor[v][0]; i --)
      if (ancestor[u][i] != ancestor[v][i])
        u = ancestor[u][i], v = ancestor[v][i];

    return(ancestor[u][0]);
  }
};
LCA t1, t2;

const int maxN = 2e5; int n, m;
bool has1[maxN], has2[maxN];
struct Edge { int u, v; };
unordered_map<int, int> edgeMap[maxN];
Edge edges[maxN];

int main()
{
  int hehe = 0;
  while (~scanf("%d %d", &n, &m))
  {
    if (hehe++) printf("--------------------------\n");
    for (int i = 0; i < m; ++i)
    {
      edgeMap[i].clear();
      has1[i] = has2[i] = false;
    }

    for (int i = 0; i < m; ++i)
    {
      int u, v; scanf("%d %d", &u, &v); --u, --v;
      edges[i] = {u, v};
      edgeMap[u][v] = edgeMap[v][u] = i;
    }

    t1 = LCA(n);
    dsu1 = DSU(n);
    for (int i = 0; i < m; ++i)
    {
      int u = edges[i].u, v = edges[i].v;
      if (!dsu1.sameSet(u, v))
        t1.addEdge(u, v), dsu1.merge(u, v), has1[i] = true;
    }
    t1.build();
    for (int k = 0; k < 1; ++k) {
      vector<int> adds, removes;
      for (int i = 0; i < m; ++i)
        if (!has1[i])
        {
          int u = edges[i].u, v = edges[i].v;
          int lca = t1.lca(u, v);
          if (lca != u && lca != v)
          {
            adds.push_back(i);
            assert(u != 0 && v != 0);
            int parent = t1.ancestor[u][0];
            int lca2 = t1.lca()
            removes.push_back(edgeMap[u][parent]);
          }
        }
      for (int i : adds)
      {
        DEBUG printf("\tadds   : %d %d\n", edges[i].u + 1, edges[i].v + 1);
        has1[i] = true;
      }
      for (int i : removes)
      {
        DEBUG printf("\tremoves: %d %d\n", edges[i].u + 1, edges[i].v + 1);
        has1[i] = false;
      }
    }

    t2 = LCA(n);
    dsu2 = DSU(n);
    for (int i = 0; i < m; ++i)
    {
      int u = edges[i].u, v = edges[i].v;
      if (!dsu2.sameSet(u, v))
        t2.addEdge(u, v), dsu2.merge(u, v), has2[i] = true;
    }
    t2.build();
    for (int k = 0; k < 1; ++k) {
      vector<int> adds, removes;
      for (int i = 0; i < m; ++i)
        if (!has2[i])
        {
          int u = edges[i].u, v = edges[i].v;
          int lca = t2.lca(u, v);
          if (lca == v) swap(u, v);
          if (lca == u)
          {
            adds.push_back(i);
            int w = v;
            removes.push_back(edgeMap[w][t2.ancestor[w][0]]);
          }
        }
      for (int i : adds)
      {
        DEBUG printf("\tadds   : %d %d\n", edges[i].u + 1, edges[i].v + 1);
        has2[i] = true;
      }
      for (int i : removes)
      {
        DEBUG printf("\tremoves: %d %d\n", edges[i].u + 1, edges[i].v + 1);
        has2[i] = false;
      }
    }

    for (int i = 0; i < m; ++i)
      if (has1[i])
        printf("%d %d\n", edges[i].u + 1, edges[i].v + 1);
    for (int i = 0; i < m; ++i)
      if (has2[i])
        printf("%d %d\n", edges[i].u + 1, edges[i].v + 1);
  }
  return 0;
}
