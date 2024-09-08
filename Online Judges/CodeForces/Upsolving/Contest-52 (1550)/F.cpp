#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int minimum, maximum;
  Data operator+(const Data &other)
  {
    return Data{min(minimum, other.minimum), max(maximum, other.maximum)};
  }
};
const Data nil = Data{(int)1e9, (int)-1e9};

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

const int maxN = 2e5; int n, q, s, d;
int a[maxN];

int main()
{
  int hehe = 0;
  while (~scanf("%d %d %d %d", &n, &q, &s, &d))
  {
    if (hehe++) printf("------------\n");
    s--;

    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    segtree = Segtree<Data>(n - 1, nil);
    for (int i = 1; i < n; i++)
      segtree.data[i - 1] = Data{a[i] - a[i - 1], a[i] - a[i - 1]};
    segtree.build();

    for (int qq = 1; qq <= q; qq++)
    {
      int i, k; scanf("%d %d", &i, &k); i--;
      if (i == s) printf("YES\n");
      else
      {
        int l = min(i, s), r = max(i, s) - 1;
        Data res = segtree.query(l, r);
        printf("\t%d %d - %d %d | %d %d\n", i, k, l, r, res.minimum, res.maximum);
        if (d - k <= res.minimum && d + k >= res.maximum)
          printf("YES\n");
        else
          printf("NO\n");
      }
    }
  }
  return 0;
}
