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
      st[i] = data[lo] = value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

int main()
{
  int n; scanf("%d", &n);
  segtree = Segtree<Data>(n, nil);
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
      int pos, value; scanf("%d %d", &pos, &value);
      segtree.update(pos, Data{value});
      printf("Update(%d with %d)\n", pos, value);
    }
  }
  return(0);
}
