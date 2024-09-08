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
const Data nil = Data{(int)1e6, (int)-1e6};

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

const int maxN = 2e5; int n, m;
char s[maxN + 1];

int lmin[maxN + 1], rmin[maxN + 1];
int lmax[maxN + 1], rmax[maxN + 1];
int lat[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    scanf(" %s", s);
    segtree = Segtree<Data>(n + 1, nil);

    int x = 0;
    lmin[0] = 0, lmax[0] = 0;
    lat[0] = 0;
    segtree.data[0] = Data{0, 0};
    for (int i = 0; i < n; i++)
    {
      x += s[i] == '+' ? 1 : -1;
      lat[i + 1] = x;
      segtree.data[i + 1] = Data{x, x};
      lmin[i + 1] = min(lmin[i], x);
      lmax[i + 1] = max(lmax[i], x);
    }
    segtree.build();
    rmin[n] = 0, rmax[n] = 0;
    x = 0;
    for (int i = n - 1; i >= 0; i--)
    {
      x += s[i] == '+' ? 1 : -1;
      rmin[i] = min(rmin[i + 1], x);
      rmax[i] = max(rmax[i + 1], x);
    }

    for (int i = 0; i < m; i++)
    {
      int lo, hi; scanf("%d %d", &lo, &hi); lo--, hi--;
      int ans = 0;
      if (lo == 0 && hi == n - 1)
      {
        ans = 1;
        DEBUG printf("\tnothing b    [%d : %d]: \n", lo, hi);
      }
      else if (lo == 0)
      {
        ans = rmax[hi + 1] - rmin[hi + 1] + 1;
        DEBUG printf("\tleft border  [%d : %d]: %d %d\n", lo, hi, rmin[hi + 1], rmax[hi + 1]);
      }
      else if (hi == n - 1)
      {
        ans = lmax[lo] - lmin[lo] + 1;
        DEBUG printf("\tright border [%d : %d]: %d %d\n", lo, hi, lmin[lo], lmax[lo]);
      }
      else
      {
        int mx = max(lmax[lo], (lat[lo] - lat[hi + 1]) + segtree.query(hi + 2, n).maximum);
        int mn = min(lmin[lo], (lat[lo] - lat[hi + 1]) + segtree.query(hi + 2, n).minimum);
        ans = mx - mn + 1;
        DEBUG printf("\tall     b    [%d : %d]: %d %d | %d %d | %d %d | %d %d\n", lo, hi, lat[lo], lat[hi + 1], lmin[lo], lmax[lo], rmin[hi + 1], rmax[hi + 1], mn, mx);
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
