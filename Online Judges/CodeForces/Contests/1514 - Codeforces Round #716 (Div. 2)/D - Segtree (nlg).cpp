#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, q;
int a[maxN];
vector<int> pos[maxN + 1];

int cntInRange(int v, int l, int r)
{
  if (v == -1) return -1;
  return upper_bound(pos[v].begin(), pos[v].end(), r) - lower_bound(pos[v].begin(), pos[v].end(), l);
}

struct Data
{
  int value, cnt;
  Data operator+(const Data &other)
  {
    if (value == other.value) return Data{value, cnt + other.cnt};
    if (cnt > other.cnt) return Data{value, cnt - other.cnt};
    return Data{other.value, other.cnt - cnt};
  }
};
const Data nil = Data{-1, 0};

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
  while (~scanf("%d %d", &n, &q))
  {
    for (int i = 0; i <= n; i++)
      pos[i].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      pos[a[i]].push_back(i);
    }
    
    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
      segtree.data[i] = Data{a[i], 1};
    segtree.build();

    for (int i = 0; i < q; i++)
    {
      int l, r; scanf("%d %d", &l, &r); l--, r--;

      int mostRep = segtree.query(l, r).value;
      int freq = cntInRange(mostRep, l, r);

      DEBUG printf("\t%d %d\n", mostRep, freq);
      printf("%d\n", max(1, freq - (r - l + 1 - freq)));
    }
  }
  return 0;
}