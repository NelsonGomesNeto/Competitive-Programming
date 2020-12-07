#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int h[maxN];
struct Edge
{
  int to;
  bool operator<(const Edge &other) const { return h[to] < h[other.to]; }
};
vector<Edge> tree[maxN];

int calcHeight(int u = 0, int prv = -1)
{
  for (auto &[v]: tree[u])
    if (v != prv)
      h[u] = max(h[u], 1 + calcHeight(v, u));
  return h[u];
}

struct Data
{
  int dist, node;
  Data operator+(const Data &other)
  {
    if (dist < other.dist)
      return *this;
    return other;
  }
};
const Data nil = Data{maxN + 1, -1};

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
      st[i].dist += lazy[i].dist;
      if (lo != hi)
      {
        lazy[2*i].dist += lazy[i].dist;
        lazy[2*i + 1].dist += lazy[i].dist;
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
      lazy[i] = value, pending[i] = op;
      lazyUpdate(i, lo, hi);
      return;
    }
    int mid = (lo + hi) >> 1;
    update(op, ulo, uhi, value, 2*i, lo, mid), update(op, ulo, uhi, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
LazySegtree<Data> segtree;
bool dfs(int k, int u = 0, int prv = -1)
{
  for (auto &[v]: tree[u])
    segtree.update(1, v, v, Data{1, 0});

  bool can = true;
  for (auto &[v]: tree[u])
    if (v != prv)
    {
      int d = segtree.query(v, v).dist;
      segtree.update(1, v, v, Data{-d, 0});
      segtree.update(1, v, v, nil);

      segtree.update(1, 0, n - 1, Data{1, 0});
      can &= dfs(k, v, u);
      segtree.update(1, 0, n - 1, Data{-1, 0});
    }

  if (u == 0) return can;
  else
  {
    Data closest = segtree.query(0, n - 1);
    if (closest.dist <= k)
      return can;
  }
  return false;
}
bool can(int k)
{
  segtree = LazySegtree<Data>(n, nil);
  for (int i = 0; i < n; i++)
  {
    segtree.data[i] = nil;
    segtree.data[i].node = i;
    segtree.pending[i] = 0;
    segtree.lazy[i] = Data{0, 0};
  }
  segtree.build();

  return dfs(k);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      tree[i].clear();

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back({v});
      tree[v].push_back({u});
    }

    calcHeight();
    for (int i = 0; i < n; i++)
      sort(tree[i].begin(), tree[i].end());

    int lo = 0, hi = n;
    while (lo < hi)
    {
      int mid = (lo + hi) >> 1;
      if (can(mid)) hi = mid;
      else lo = mid + 1;
    }
    printf("%d\n", lo);
  }
  return 0;
}