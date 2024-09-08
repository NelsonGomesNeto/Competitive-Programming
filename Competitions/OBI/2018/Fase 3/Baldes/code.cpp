#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int inf = 1e9;
struct Data
{
  int minimum, maximum, delta;
  Data operator+(const Data &other)
  {
    if (minimum == inf) return other;
    if (other.minimum == inf) return *this;
    return Data
    {
      min(minimum, other.minimum),
      max(maximum, other.maximum),
      max({delta, other.delta, maximum - other.minimum, other.maximum - minimum})
    };
  }
};
const Data nil = Data{inf, -inf, 0};

// DON'T FORGET TO DEFINE THE NIL!!!
template<class T>
struct Segtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  Segtree() { }
  Segtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size);
    st.resize(4*size);
  }
  Segtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
  void update(int pos, T value) { update(pos, value, 1, 0, size - 1); }
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
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
  void update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i].minimum = min(st[i].minimum, value.minimum);
      st[i].maximum = max(st[i].maximum, value.maximum);
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

const int maxN = 1e5; int n, m;
int buckets[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &buckets[i]);
      segtree.data[i] = Data{buckets[i], buckets[i], 0};
    }
    segtree.build();

    for (int i = 0; i < m; i++)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int p, i; scanf("%d %d", &p, &i); i--;

        segtree.update(i, Data{p, p});
      }
      else
      {
        int l, r; scanf("%d %d", &l, &r); l--, r--;

        Data ans = segtree.query(l, r);
        printf("%d\n", ans.delta);
      }
    }
  }
  return 0;
}