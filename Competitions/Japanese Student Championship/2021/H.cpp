#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  bool had; lli cost;
  Data operator+(const Data &other)
  {
    return Data{had || other.had, cost*had + other.cost*other.had};
  }
};
const Data nil = Data{false, 0};

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
    data.resize(size);
    st.resize(4*size);
    lazy.resize(4*size);
    pending.resize(4*size);
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
      st[i].had = lazy[i].had;
      if (lo != hi)
      {
        lazy[2*i] = lazy[2*i + 1] = lazy[i];
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
      lazy[i].had = value.had, pending[i] = op;
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

struct DSU
{
  int size;
  vector<int> parents;
  DSU() { parents.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init() { parents.resize(size); fill(parents.begin(), parents.end(), -1); }
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
DSU dsu;

const int maxN = 2e5; int n, m;
int a[maxN];
lli c[maxN];
pair<int, int> cargoes[maxN];
vector<vector<int>> tree;

int edgeIdx[maxN];
void addEdge(int u)
{
  tree[u].push_back(u + n);
  tree[u + n].push_back(u);
  tree[u + n].push_back(a[u]);
  tree[a[u]].push_back(u + n);
}
lli eval()
{
  hld = HeavyLightDecomposition<Data>(tree, nil);
  hld.build();
  for (int u = 0; u < n; u++)
  {
    hld.segtree.data[hld.position[u]] = Data{false, 0};
    hld.segtree.data[hld.position[u + n]] = Data{false, c[u]};
  }
  hld.segtree.build();

  for (auto &[u, v]: cargoes)
    hld.updatePath(u, v, Data{true, -1});

  lli total = 0;
  for (int u = 0; u < n; u++)
  {
    Data res = hld.queryNode(u + n);
    printf("\t\t%d ? %d -[%lld]> %d\n", res.had, u, c[u], a[u]);
    total += res.cost * res.had;
  }
  return total;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d %lld", &a[i], &c[i]);
      a[i]--;
    }
    for (int i = 0; i < m; i++)
    {
      scanf("%d %d", &cargoes[i].first, &cargoes[i].second);
      cargoes[i].first--, cargoes[i].second--;
    }

    dsu = DSU(n);

    lli ans = 1e18;
    set<int> firsts;
    int extra = -1;
    do
    {
      dsu.init();
      extra = -1;
      tree.clear();
      tree.resize(2*n);

      bool done = false;
      for (int u: firsts)
      {
        addEdge(u);
        if (dsu.root(u) == dsu.root(a[u]))
          done = true;
        dsu.merge(u, a[u]);
      }
      if (done)
        break;

      for (int i = 0; i < n; i++)
        if (!firsts.count(i))
        {
          if (extra == -1 && dsu.root(i) == dsu.root(a[i]))
            extra = i, firsts.insert(i);
          else
            addEdge(i);
          dsu.merge(i, a[i]);
        }
      ans = min(ans, eval());
      DEBUG printf("\tout %d (%d) - %lld\n", extra + 1, a[extra] + 1, eval());
    }
    while (extra != -1);

    printf("%lld\n", ans);
  }
  return 0;
}