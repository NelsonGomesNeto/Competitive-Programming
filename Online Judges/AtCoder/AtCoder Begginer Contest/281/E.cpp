#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

vector<pair<lli, int>> mapa;
vector<int> revMap;

struct Data
{
  int cnt; lli sum;
  Data operator+(const Data &other)
  {
    return Data{cnt + other.cnt, sum + other.sum};
  }
};
const Data nil = Data{0, 0};

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
      st[i] = st[i] + value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

const int maxN = 2e5;
int n, m, k;
lli a[maxN];
lli ans[maxN];

lli getSum()
{
  int lo = 0, hi = n - 1;
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    Data res = segtree.query(0, mid);
    if (res.cnt >= k) hi = mid;
    else lo = mid + 1;
  }
  return segtree.query(0, lo).sum;
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    mapa.clear(); mapa.resize(n);
    revMap.clear(); revMap.resize(n);
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      mapa[i] = make_pair(a[i], i);
    }
    sort(mapa.begin(), mapa.end());
    for (int i = 0; i < n; i++)
      revMap[mapa[i].second] = i;

    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; ++i)
      segtree.data[i] = nil;
    segtree.build();

    for (int i = 0; i < m; ++i)
      segtree.update(revMap[i], Data{1, a[i]});

    ans[0] = getSum();
    for (int i = m; i < n; ++i)
    {
      segtree.update(revMap[i], Data{1, a[i]});
      segtree.update(revMap[i - m], Data{-1, -a[i - m]});
      ans[i - m + 1] = getSum();
    }

    for (int i = 0; i < n - m + 1; ++i)
      printf("%lld%c", ans[i], i + 1 < n - m + 1 ? ' ' : '\n');
  }
  return 0;
}
