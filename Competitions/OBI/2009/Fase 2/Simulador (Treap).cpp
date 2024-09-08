#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli apSum(lli a1, lli an)
{
  lli n = abs(an - a1) + 1LL;
  // printf("apSum: %lld %lld %lld\n", a1, an, n);
  return n * (a1 + an) >> 1LL;
}

struct Data
{
  int lo, hi; lli sum;
  Data(int lo, int hi) : lo(lo), hi(hi)
  {
    sum = apSum(lo, hi);
  }
  Data operator+(const Data &other)
  {
    if (lo == -1) return other;
    if (other.lo == -1) return *this;
    return Data(min(lo, other.lo), max(hi, other.hi));
  }
};
const Data nil = Data(-1, -1);

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
      lazy[i] = lazy[i] + value, pending[i] = op;
      lazyUpdate(i, lo, hi);
      return;
    }
    int mid = (lo + hi) >> 1;
    update(op, ulo, uhi, value, 2*i, lo, mid), update(op, ulo, uhi, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
LazySegtree<Data> segtree;

const lli maxN = 1e9;
const int maxM = 1e3;
int n, m;

struct Query
{
  char op; int lo, hi;
  void read() { scanf("%d %d", &lo, &hi); }
};
Query queries[maxM];
vector<int> xs;

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < m; i ++)
      queries[i].read();
    
    xs.clear();
    for (int i = 0; i < m; i ++)
    {
      xs.push_back(queries[i].lo);
      xs.push_back(queries[i].hi);
    }
    sort(xs.begin(), xs.end());
    xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));

    for (int i = 0; i < m; i++)
  }


  return(0);
}