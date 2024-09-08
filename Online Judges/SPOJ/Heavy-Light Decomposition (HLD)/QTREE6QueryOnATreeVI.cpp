#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
Using HLD, I can climb up while the above nodes have my color
Let's call it: mcr = "my color's root"
On mcr, we can perform a subtree query to count how many are connected to me, since this will retrieve the same answer

Data may have the whiteSubtreeSize and blackSubtreeSize
  But you will need a third variable to tell which color is which
On updating: 
*/

struct Data
{
  int blackSubtreeSize, whiteSubtreeSize, blackCount, whiteCount;
  Data operator+(const Data &other)
  {
    return Data{blackSubtreeSize + other.blackSubtreeSize,
                whiteSubtreeSize + other.whiteSubtreeSize,
                blackCount + other.blackCount,
                whiteCount + other.whiteCount};
  }
  Data operator*(const int other)
  {
    return *this;
  }
};
const Data nil = Data{0, 0, 0, 0};

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
    st.resize(4*size, nil);
    lazy.resize(4*size, nil);
    pending.resize(4*size, 0);
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
  vector<int> eulerTour;
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
    heavyPaths.clear(), eulerTour.clear();
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
        head[u] = heavyPaths[i][0], tail[u] = heavyPaths[i].back();
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
    eulerTour.push_back(u);

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

const int maxN = 1e5; int n, q;
vector<vector<int>> tree;
bool isWhite[maxN];

int climbToHighest(int u, Data delta = nil)
{
  int curr = u;
  int highest = u;
  while (curr != 0 && (isWhite[u] ?
            hld.segtree.query(hld.position[hld.head[curr]], hld.position[curr]).whiteCount :
            hld.segtree.query(hld.position[hld.head[curr]], hld.position[curr]).blackCount)
          == hld.position[curr] - hld.position[hld.head[curr]] + 1)
  {
    highest = hld.head[curr];
    curr = hld.parent[hld.head[curr]];
  }
  if (isWhite[curr] != isWhite[u])
    return highest;

  int lo = hld.position[hld.head[curr]], hi = hld.position[curr], p = hld.position[curr];
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if ((isWhite[u] ?
          hld.segtree.query(mid, p).whiteCount :
          hld.segtree.query(mid, p).blackCount)
        == p - mid + 1)
      hi = mid;
    else
      lo = mid + 1;
  }
  if (isWhite[hld.eulerTour[lo]] == isWhite[u])
    highest = hld.eulerTour[lo];

  return highest;
}
int climbAndUpdate(int u, int above, Data delta)
{
  int highest = climbToHighest(u);
  highest = highest != 0 ? hld.parent[highest] : highest;
  if (highest != u)
    hld.updatePath(above, highest, delta);
  return highest;
}

int main()
{
  while (~scanf("%d", &n))
  {
    tree.clear();
    tree.resize(n);
    for (int i = 0; i < n; i++) isWhite[i] = false;
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    hld = HeavyLightDecomposition<Data>(tree, nil);
    hld.build();
    for (int u = 0; u < n; u++)
      hld.segtree.data[hld.position[u]] = Data{hld.subtreeSize[u], 0, 1, 0};
    hld.segtree.build();

    DEBUG {
      printf("Heavy Paths:\n");
      for (int i = 0; i < hld.heavyPaths.size(); i++)
      {
        printf("\t");
        for (int j = 0; j < hld.heavyPaths[i].size(); j++)
          printf("%d%c", hld.heavyPaths[i][j] + 1, j < hld.heavyPaths[i].size() - 1 ? ' ' : '\n');
      }
      printf("-------\n");
    }

    scanf("%d", &q);
    while (q--)
    {
      int op, u; scanf("%d %d", &op, &u); u--;
      DEBUG printf("\t%d %d\n", op, u + 1);
      if (op == 0)
      {
        int highest = climbToHighest(u);
        DEBUG printf("\t\thighest query: %d\n", highest + 1);
        printf("%d\n", isWhite[u] ? hld.queryNode(highest).whiteSubtreeSize : hld.queryNode(highest).blackSubtreeSize);
      }
      else
      {
        hld.updateNode(u, Data{isWhite[u], !isWhite[u], 0, 0});
        Data uValue = hld.queryNode(u);
        Data remDelta = Data{-!isWhite[u]*uValue.blackSubtreeSize, -isWhite[u]*uValue.whiteSubtreeSize, 0, 0};
        Data addDelta = Data{isWhite[u]*uValue.blackSubtreeSize, !isWhite[u]*uValue.whiteSubtreeSize, 0, 0};
        int above = u != 0 ? hld.parent[u] : 0;

        // climb to the first with a different color
        int highest = climbAndUpdate(u, above, remDelta);
        DEBUG printf("\tupdating %d (%d) from %d: %d || %d %d\n", u + 1, above + 1, isWhite[u], highest + 1, remDelta.blackSubtreeSize, remDelta.whiteSubtreeSize);

        hld.updateNode(u, Data{0, 0, isWhite[u] ? 1 : -1, isWhite[u] ? -1 : 1});
        isWhite[u] = !isWhite[u];

        // climb to the first with a different color
        highest = climbAndUpdate(u, above, addDelta);
        DEBUG printf("\tupdating %d (%d) to %d: %d || %d %d\n", u + 1, above + 1, isWhite[u], highest + 1, addDelta.blackSubtreeSize, addDelta.whiteSubtreeSize);

        hld.updateNode(u, Data{-isWhite[u], -!isWhite[u], 0, 0});

        DEBUG {
          printf("\tafter update:\n");
          for (int u = 0; u < n; u++)
            printf("\t\t%d | b: %d, w: %d || b: %d, w: %d\n", u + 1, hld.queryNode(u).blackSubtreeSize, hld.queryNode(u).whiteSubtreeSize, hld.queryNode(u).blackCount, hld.queryNode(u).whiteCount);
        }
      }
    }
  }
  return 0;
}