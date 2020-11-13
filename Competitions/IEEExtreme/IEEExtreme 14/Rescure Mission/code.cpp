#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxQ = 5e3; int n, d;
// lli s[maxN];

struct Query
{
  int lo, hi; lli v;
  void read() { scanf("%d %d %lld", &lo, &hi, &v); lo--, hi--; }
};
Query queries[maxQ];

// lli rangeCnt[maxN];

struct Data
{
  lli value;
  Data operator+(const Data &other)
  {
    return Data{value + other.value};
  }
  Data operator*(const lli other)
  {
    return Data{value * other};
  }
};
const Data nil = {0};

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
      st[i] = st[i] + (lazy[i] * (lli)(hi - lo + 1));
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

LazySegtree<Data> rangeCnt, s;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    s = LazySegtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
    {
      lli ss; scanf("%lld", &ss);
      s.data[i] = Data{ss};
    }
    s.build();

    rangeCnt = LazySegtree<Data>(n, nil);
    rangeCnt.build();

    scanf("%d", &d);
    for (int i = 0; i < d; i++)
    {
      queries[i].read();
      rangeCnt.update(1, queries[i].lo, queries[i].hi, Data{queries[i].v});
      // for (int j = queries[i].lo; j <= queries[i].hi; j++)
      //   rangeCnt[j] += queries[i].v;
    }

    lli ans = 0;
    for (int i = 0; i < d; i++)
    {
      Query &q = queries[i];
      rangeCnt.update(1, q.lo, q.hi, Data{-q.v});
      // for (int j = q.lo; j <= q.hi; j++)
      //   rangeCnt[j] -= q.v;

      lli total = s.query(q.lo, q.hi).value;
      DEBUG printf("\t%d %lld\n", i, total);
      lli delta = min(total, q.v);
      ans += delta;
      // for (int j = q.lo; j <= q.hi && delta; j++)
      // {
      //   lli dd = min(delta, s.query(j, j).value);
      //   s.update(1, j, j, Data{-dd});
      //   delta -= dd;
      //   // total += s[j];
      // }

      lli missing = max(0LL, total - q.v);
      priority_queue<pair<lli, int>> pq;
      for (int j = q.lo; j <= q.hi; j++)
        pq.push({rangeCnt.query(j, j).value, j});
      while (!pq.empty() && missing)
      {
        auto p = pq.top(); pq.pop();
        delta = min(missing, p.first);
        // s[p.second] += delta;
        s.update(1, p.second, p.second, Data{delta});
        missing -= delta;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}