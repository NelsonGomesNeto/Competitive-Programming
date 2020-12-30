#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int fillTimestamp, emptyTimestamp;
  Data operator+(const Data &other)
  {
    return Data{max(fillTimestamp, other.fillTimestamp), max(emptyTimestamp, other.emptyTimestamp)};
  }
};
const Data nil = Data{-1, -1};

// DON'T FORGET TO DEFINE THE NIL!!!
template<class T>
struct LazySegtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  vector<T> lazy;
  vector<int> pending;
  LazySegtree() { }
  LazySegtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size, nil);
    st.resize(4*size, nil);
    lazy.resize(4*size, nil);
    pending.resize(4*size, 0);
  }
  LazySegtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    lazy.resize(4*size);
    pending.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
  void update(int op, int ulo, int uhi, T value) { update(op, ulo, uhi, value, 1, 0, size - 1); }
  void build(int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i] = data[lo];
      return;
    }
    int mid = (lo + hi) >> 1;
    build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
  void lazyUpdate(int i, int lo, int hi)
  {
    if (pending[i])
    {
      st[i] = st[i] + lazy[i];
      if (lo != hi)
      {
        lazy[2*i] = lazy[2*i] + lazy[i];
        lazy[2*i + 1] = lazy[2*i + 1] + lazy[i];
        pending[2*i] = pending[2*i + 1] = pending[i];
      }
      lazy[i] = nil, pending[i] = 0;
    }
  }
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    lazyUpdate(i, lo, hi);
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
  void update(int op, int ulo, int uhi, T &value, int i, int lo, int hi)
  {
    lazyUpdate(i, lo, hi);
    if (hi < ulo || lo > uhi) return;
    if (lo >= ulo && hi <= uhi)
    {
      lazy[i] = lazy[i] + value, pending[i] = op;
      lazyUpdate(i, lo, hi);
      return;
    }
    int mid = (lo + hi) >> 1;
    update(op, ulo, uhi, value, 2*i, lo, mid), update(op, ulo, uhi, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};

template<class T>
struct HeavyLightDecomposition
{
  int n;
  vector<vector<int>> tree;
  vector<int> subtreeSize, level, parent;
  vector<int> heavyPath, position, head, tail;
  vector<vector<int>> heavyPaths;
  LazySegtree<T> segtree;

  HeavyLightDecomposition() { }
  HeavyLightDecomposition(int n, T nil) : n(n)
  {
    tree.resize(n);
    init();
  }
  HeavyLightDecomposition(vector<vector<int>> &t, T nil) : tree(t)
  {
    n = tree.size();
    init();
  }
  void init()
  {
    subtreeSize.resize(n), level.resize(n), parent.resize(n);
    heavyPath.resize(n), position.resize(n), head.resize(n), tail.resize(n);
    heavyPaths.clear();
    segtree = LazySegtree<T>(n, nil);
  }
  void build()
  {
    hldPrecalculations();
    buildHeavyPaths();
    // Build segtree
    for (int i = 0, j = 0; i < heavyPaths.size(); i++)
      for (int u: heavyPaths[i])
      {
        heavyPath[u] = i, position[u] = j++;
        head[u] = heavyPaths[heavyPath[u]][0], tail[u] = heavyPaths[heavyPath[u]].back();
      }
  }

  void hldPrecalculations(int u = 0, int prv = -1)
  {
    subtreeSize[u] = 1;
    for (int v: tree[u])
      if (v != prv)
      {
        level[v] = level[u] + 1, parent[v] = u;
        hldPrecalculations(v, u);
        subtreeSize[u] += subtreeSize[v];
      }
  }
  void buildHeavyPaths(int u = 0, int prv = -1, int currIndex = 0)
  {
    if (heavyPaths.empty()) heavyPaths.push_back(vector<int>());
    heavyPaths[currIndex].push_back(u);

    for (int v: tree[u])
      if (v != prv && 2*subtreeSize[v] >= subtreeSize[u]) // heavy-edge
        buildHeavyPaths(v, u, currIndex);
    for (int v: tree[u])
      if (v != prv && 2*subtreeSize[v] < subtreeSize[u]) // light-edge
      {
        heavyPaths.push_back(vector<int>());
        buildHeavyPaths(v, u, heavyPaths.size() - 1);
      }
  }
  T queryNode(int u)
  { return segtree.query(position[u], position[u]); }
  void updateNode(int u, T newValue)
  { segtree.update(1, position[u], position[u], newValue); }
  T queryPath(int u, int v)
  {
    T ans = nil;
    for (; heavyPath[u] != heavyPath[v]; u = parent[head[u]])
    {
      if (level[head[u]] < level[head[v]]) swap(u, v);
      ans = ans + segtree.query(position[head[u]], position[u]);
    }
    if (level[u] < level[v]) swap(u, v);
    return ans + segtree.query(position[v], position[u]);
  }
  void updatePath(int u, int v, T newValue)
  {
    T ans = nil;
    for (; heavyPath[u] != heavyPath[v]; u = parent[head[u]])
    {
      if (level[head[u]] < level[head[v]]) swap(u, v);
      segtree.update(1, position[head[u]], position[u], newValue);
    }
    if (level[u] < level[v]) swap(u, v);
    segtree.update(1, position[v], position[u], newValue);
  }
  T querySubtree(int u)
  { return segtree.query(position[u], position[u] + subtreeSize[u] - 1); }
  void updateSubtree(int u, T newValue)
  { segtree.update(1, position[u], position[u] + subtreeSize[u] - 1, newValue); }
};
HeavyLightDecomposition<Data> hld;

const int maxN = 5e5; int n, q;
vector<vector<int>> tree;

int main()
{
  while (~scanf("%d", &n))
  {
    tree.clear();
    tree.resize(n);
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    hld = HeavyLightDecomposition<Data>(tree, nil);
    hld.build();
    for (int u = 0; u < n; u++)
      hld.segtree.data[hld.position[u]] = nil;
    hld.segtree.build();

    DEBUG {
      printf("Heavy Paths:\n");
      for (int i = 0; i < hld.heavyPaths.size(); i++)
      {
        printf("\t");
        for (int j = 0; j < hld.heavyPaths[i].size(); j++)
          printf("%d%c", hld.heavyPaths[i][j], j < hld.heavyPaths[i].size() - 1 ? ' ' : '\n');
      }
      printf("\n");
    }

    scanf("%d", &q);
    for (int qq = 1; qq <= q; qq++)
    {
      int op, u; scanf("%d %d", &op, &u); u--;
      DEBUG printf("\t%d %d\n", op, u + 1);
      if (op == 1) // to fill
        hld.updateSubtree(u, Data{qq, -1});
      else if (op == 2) // to empty
        hld.updatePath(u, 0, Data{-1, qq});
      else // is full?
      {
        Data ans = hld.queryPath(u, u);
        printf("%d\n", ans.fillTimestamp > ans.emptyTimestamp);
      }
    }
  }
  return 0;
}