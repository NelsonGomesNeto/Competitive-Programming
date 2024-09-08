#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int freq, i;
  Data operator+(const Data &other)
  {
    if (freq == 0 && other.freq == 0)
      return Data{0, max(i, other.i)};
    if (freq == 0) return *this;
    if (other.freq == 0) return other;

    return *this;
  }
};
const Data nil = Data{1, -1};

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

const int maxN = 1e5; int n;
struct Patient
{
  int l, r, idx;
  void read() { scanf("%d %d", &l, &r); l--, r--; }
  bool operator<(const Patient &other) const { return r < other.r || (r == other.r && l < other.l); }
};
Patient p[maxN];
int ans[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    segtree = Segtree<Data>(n, nil);

    for (int i = 0; i < n; i++)
    {
      p[i].read(), p[i].idx = i;
      ans[i] = -1;
      segtree.data[i] = Data{0, i};
    }
    segtree.build();
    sort(p, p+n);

    for (int i = 0; i < n; i++)
    {
      Data res = segtree.query(p[i].l, p[i].r);
      if (res.freq) break;

      ans[res.i] = p[i].idx;
      segtree.update(res.i, Data{1, res.i});
    }

    if (*min_element(ans, ans+n) == -1) printf("impossible\n");
    else for (int i = 0; i < n; i++) printf("%d%c", ans[i] + 1, i + 1 < n ? ' ' : '\n');
  }
  return 0;
}