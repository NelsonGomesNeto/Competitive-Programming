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

int main()
{
  int n; scanf("%d", &n);
  LazySegtree<Data> segtree(n, Data{0});
  for (int i = 0; i < n; i ++) scanf("%d", &segtree.data[i].value);
  segtree.build();

  char kind[2];
  while (scanf(" %s", kind) != EOF)
  {
    if (kind[0] == 'Q')
    {
      int lo, hi; scanf("%d %d", &lo, &hi);
      printf("Sum(%d, %d) = %d\n", lo, hi, segtree.query(lo, hi).value);
    }
    else if (kind[0] == 'U')
    {
      int lo, hi, value; scanf("%d %d %d", &lo, &hi, &value);
      segtree.update(1, lo, hi, Data{value});
      printf("Update([%d : %d] with %d)\n", lo, hi, value);
    }
  }
  return(0);
}
