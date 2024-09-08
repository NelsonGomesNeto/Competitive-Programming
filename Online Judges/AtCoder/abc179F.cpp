#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, q;

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{min(value, other.value)};
  }
  Data operator*(const int other)
  {
    return Data{value};
  }
};
const Data nil = Data{maxN};

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
    lazy.resize(4*size, nil);
    pending.resize(4*size);
  }
  LazySegtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    lazy.resize(4*size, nil);
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
      lazy[i] = value, pending[i] = op;
      lazyUpdate(i, lo, hi);
      return;
    }
    int mid = (lo + hi) >> 1;
    update(op, ulo, uhi, value, 2*i, lo, mid), update(op, ulo, uhi, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
LazySegtree<Data> r, b;

int main()
{
  while (scanf("%d %d", &n, &q) != EOF)
  {
    r = LazySegtree<Data>(n, nil);
    b = LazySegtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
      r.data[i].value = b.data[i].value = n - 1;
    r.build(), b.build();

    lli ans = (lli)(n - 2) * (n - 2);
    for (int i = 0; i < q; i++)
    {
      int op, x; scanf("%d %d", &op, &x); x--;
      if (op == 1) // (1, x), bottom
      {
        int upMost = b.query(x, x).value;
        int delta = max(0, upMost - 1);
        DEBUG printf("\t%d %d - %d - %d\n", op, x, upMost, delta);
        ans -= delta;
        r.update(1, 0, upMost, Data{x});
      }
      else // (x, 1) right
      {
        int leftMost = r.query(x, x).value;
        int delta = max(0, leftMost - 1);
        DEBUG printf("\t%d %d - %d - %d\n", op, x, leftMost, delta);
        ans -= delta;
        b.update(1, 0, leftMost, Data{x});
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}