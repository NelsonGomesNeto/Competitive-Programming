#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{value + other.value};
  }
  Data operator*(const int other)
  {
    return Data{value * other};
  }
};
const Data nil = Data{0};

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
      st[i] = lazy[i] * (hi - lo + 1);
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

const int maxN = 2e5; int n, m;
const int mod = 1e9 + 7;
struct Seg
{
  int l, r; int x;
  void read() { scanf("%d %d %d", &l, &r, &x); l--, r--; }
};
Seg segs[maxN];
int a[maxN];

int memo[maxN][2];
int pot; int shift;
int calc(int i = 0, bool has = false)
{
  if (i == n) return pot * has;
  int &ans = memo[i][has];
  if (ans != -1) return ans;
  return ans = (calc(i + 1, has ^ ((a[i] >> shift) & 1)) + calc(i + 1, has)) % mod;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    segtree = LazySegtree<Data>(n, nil);
    segtree.build();
    for (int i = 0; i < m; i++)
    {
      segs[i].read();
      segtree.update(1, segs[i].l, segs[i].r, Data{segs[i].x});
    }

    for (int i = 0; i < n; i++)
      a[i] = segtree.query(i, i).value;

    DEBUG {
      int ans2 = calc();
      printf("\t%d\n", ans2);
      for (int i = 0; i < n; i++)
        printf("%d%c", a[i], i + 1 < n ? ' ' : '\n');
    }

    int ans = 0;
    for (int bit = 0; bit < 30; bit++)
    {
      shift = bit, pot = 1LL << bit;
      for (int i = 0; i < n; i++) memo[i][0] = memo[i][1] = -1;
      ans = (ans + calc()) % mod;
    }
    printf("%d\n", ans);
  }
  return 0;
}
