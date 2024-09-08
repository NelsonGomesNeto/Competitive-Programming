#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int value, ulo;
  Data operator+(const Data &other)
  {
    return Data{min(value, other.value), 0};
  }
  Data operator*(const int other)
  {
    return Data{value * other};
  }
};
const Data nil = Data{(int)1e7, 0};

// DON'T FORGET TO DEFINE THE NIL!!!
struct LazySegtree
{
  int size;
  vector<Data> data;
  vector<Data> st;
  vector<Data> lazy;
  vector<int> pending;
  LazySegtree(int size) : size(size)
  {
    data.resize(size);
    st.resize(4*size);
    lazy.resize(4*size);
    pending.resize(4*size);
  }
  LazySegtree(vector<Data> &data) : size(data.size()), data(data)
  {
    st.resize(4*size);
    lazy.resize(4*size);
    pending.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  Data query(int qlo, int qhi) { if (qhi < 0 || qlo > qhi) return nil; return query(qlo, qhi, 1, 0, size - 1); }
  void update(int op, int ulo, int uhi, Data value) { update(op, ulo, uhi, value, 1, 0, size - 1); }
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
      st[i] = Data{lo - lazy[i].ulo + lazy[i].value, 0};
      if (lo != hi)
      {
        lazy[2*i] = lazy[i];
        lazy[2*i + 1] = lazy[i];
        pending[2*i] = pending[2*i + 1] = pending[i];
      }
      lazy[i] = nil, pending[i] = 0;
    }
  }
  Data query(int qlo, int qhi, int i, int lo, int hi)
  {
    lazyUpdate(i, lo, hi);
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
  void update(int op, int ulo, int uhi, Data &value, int i, int lo, int hi)
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

const int maxN = 2e5;
int n, m; 
struct Seg
{
  int lo, hi;
  void read() { scanf("%d %d", &lo, &hi); lo--, hi--; }
};
Seg segments[maxN];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      segments[i].read();

    LazySegtree segtree = LazySegtree(m);
    for (int i = 0; i < m; i++) segtree.data[i] = Data{0, 0};
    segtree.build();

    for (int i = 0; i < n; i++)
    {
      segtree.update(1, segments[i].lo, segments[i].hi, nil);
      DEBUG printf("\t%d\n", segtree.query(0, m - 1).value);
      int ans = i + 1 + segtree.query(0, m - 1).value;
      printf("%d\n", ans >= 1e7 ? -1 : ans);
      segtree.update(1, segments[i].lo, segments[i].hi, Data{segtree.query(segments[i].lo - 1, segments[i].lo - 1).value + 1, segments[i].lo});
    }
  }
  return 0;
}