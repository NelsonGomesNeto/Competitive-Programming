#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  lli value;
  Data operator+(const Data &other)
  {
    return Data{value ^ other.value};
  }
};
const Data nil = Data{0};

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
      data[lo] = data[lo] + value;
      st[i] = data[lo];
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

const int maxN = 3e5; int n, q;
lli a[maxN];

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      segtree.data[i] = Data{a[i]};
    }
    segtree.build();

    while (q--)
    {
      int op, x, y; scanf("%d %d %d", &op, &x, &y);
      if (op == 1)
      {
        segtree.update(x - 1, Data{y});
      }
      else if (op == 2)
      {
        printf("%lld\n", segtree.query(x - 1, y - 1).value);
      }
    }
  }
  return 0;
}