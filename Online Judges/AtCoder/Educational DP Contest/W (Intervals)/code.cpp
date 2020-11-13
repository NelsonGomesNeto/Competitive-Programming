#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 2; int n, m;
const lli inf = 1e15;
struct Interval
{
  int l, r; lli a;
  void read() { scanf("%d %d %lld", &l, &r, &a); }
};
Interval intervals[maxN];
vector<Interval> in[maxN], out[maxN];

struct Data
{
  lli value;
  Data operator+(const Data &other)
  {
    return Data{max(value, other.value)};
  }
  Data operator*(const int other)
  {
    return Data{value};
  }
};
const Data nil = {-inf};

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
      st[i].value += lazy[i].value;
      if (lo != hi)
      {
        lazy[2*i].value += lazy[i].value;
        lazy[2*i + 1].value += lazy[i].value;
        pending[2*i] = pending[2*i + 1] = pending[i];
      }
      lazy[i] = Data{0}, pending[i] = 0;
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

lli memo[maxN];
lli solve()
{
  segtree = LazySegtree<Data>(n + 1, nil);
  for (int i = 0; i <= n; i++) segtree.data[i] = Data{0};
  segtree.build();

  for (int i = 1; i <= n; i++)
  {
    for (Interval &interval: in[i])
      segtree.update(1, 0, i - 1, Data{interval.a});

    memo[i] = segtree.query(0, i - 1).value;
    segtree.update(1, i, i, Data{memo[i]});

    for (Interval &interval: out[i])
      segtree.update(1, 0, interval.l - 1, Data{-interval.a});
  }
  return max(0LL, *max_element(memo, memo+n+1));
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < maxN; i++)
      in[i].clear(), out[i].clear();
    for (int i = 0; i < m; i++)
    {
      intervals[i].read();
      in[intervals[i].l].push_back(intervals[i]);
      out[intervals[i].r].push_back(intervals[i]);
    }

    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}