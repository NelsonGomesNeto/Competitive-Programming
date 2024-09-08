#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int color, minColor, maxColor; lli colorfulness, delta;
  Data operator+(const Data &other)
  {
    if (color == -1) return other;
    if (other.color == -1) return *this;
    return Data{color, min(minColor, other.minColor), max(maxColor, other.maxColor), colorfulness + other.colorfulness, delta + other.delta};
  }
  bool canRangeUpdate()
  {
    return minColor == maxColor;
  }
};
const Data nil = Data{-1, 0, 0, 0, 0};

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
      assert(st[i].minColor == st[i].maxColor);
      st[i].colorfulness += lazy[i].delta * (hi - lo + 1);
      st[i].minColor = st[i].maxColor = st[i].color = lazy[i].color;
      if (lo != hi)
      {
        int mid = (lo + hi) >> 1;
        lazy[2*i].delta += lazy[i].delta;
        lazy[2*i].color = lazy[i].color;

        lazy[2*i + 1].delta += lazy[i].delta;
        lazy[2*i + 1].color = lazy[i].color;

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
    if (lo >= ulo && hi <= uhi && st[i].canRangeUpdate())
    {
      value.delta = abs(st[i].color - value.color);
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

const int maxN = 1e5; int n, m;

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    segtree = LazySegtree<Data>(n, nil);
    for (int i = 0; i < n; i++) segtree.data[i] = Data{i + 1, i + 1, i + 1, 0, 0};
    segtree.build();

    for (int i = 0; i < m; i++)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int l, r, x; scanf("%d %d %d", &l, &r, &x); l--, r--;
        segtree.update(1, l, r, Data{x, x, x, 0, 0});
      }
      else
      {
        int l, r; scanf("%d %d", &l, &r); l--, r--;
        Data res = segtree.query(l, r);
        printf("%lld\n", res.colorfulness);
      }
    }

    DEBUG {
      printf("\t");
      for (int i = 0; i < n; i++)
        printf("(%d, %lld)%c", segtree.query(i, i).color, segtree.query(i, i).colorfulness, i + 1 < n ? ' ' : '\n');
    }
  }
  return 0;
}