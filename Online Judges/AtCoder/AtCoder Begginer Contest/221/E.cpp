#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;
const lli mod = 998244353;

struct Data
{
  int cnt; lli total;
  Data operator+(const Data &other)
  {
    return Data{cnt + other.cnt, (total + other.total) % mod};
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
      st[i].cnt += value.cnt;
      st[i].total = (st[i].total + value.total) % mod;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

const int maxN = 3e5; int n;
lli a[maxN];
vector<lli> as;

int main()
{
  while (~scanf("%d", &n))
  {
    as.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      as.push_back(a[i]);
    }
    sort(as.begin(), as.end());
    as.resize(distance(as.begin(), unique(as.begin(), as.end())));

    for (int i = 0; i < n; i++)
      a[i] = lower_bound(as.begin(), as.end(), a[i]) - as.begin();

    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++) segtree.data[i] = nil;
    segtree.build();

    lli ans = 0;
    for (int i = n - 1; i >= 0; i--)
    {
      if (i < n - 1)
      {
        Data now = segtree.query(a[i], n - 1);
        if (now.cnt)
        {
          lli total = now.total * inv(modPow(2, i + 1)) % mod;
          DEBUG printf("\t%d - %lld - %d %lld - %lld\n", i, a[i], now.cnt, now.total, total);
          ans = (ans + total) % mod;
        }
      }
      segtree.update(a[i], Data{1, modPow(2, i)});
    }
    printf("%lld\n", ans);
  }
  return 0;
}