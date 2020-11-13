#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxH = 2e5; int n;
int h[maxN + 1]; lli a[maxN];

// 1 <= hi <= N and hi != hj for all i != j
// This probably is very important
// It means h is a permutation

lli solve(int i = 0, int prv = n)
{
  if (i == n) return 0;

  lli ans = 0;
  ans = max(ans, solve(i + 1, prv));
  if (h[i] > h[prv])
    ans = max(ans, solve(i + 1, i) + a[i]);

  return ans;
}

lli solve2()
{
  lli lis[n];
  memset(lis, 0, sizeof(lis));
  lis[0] = a[0];
  for (int i = 1; i < n; i++)
  {
    lis[i] = a[i];
    for (int prv = 0; prv < i; prv++)
      if (h[i] > h[prv])
        lis[i] = max(lis[i], lis[prv] + a[i]);
  }
  return *max_element(lis, lis+n);
}

struct Data
{
  lli value;
  Data operator+(const Data &other)
  {
    return Data{max(value, other.value)};
  }
};
const Data nil = {0};

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
lli solve3()
{
  segtree = Segtree<Data>(maxH + 1, nil);
  for (int i = 0; i <= maxH; i++)
    segtree.data[i] = nil;
  segtree.build();

  segtree.update(h[0], Data{a[0]});
  for (int i = 1; i < n; i++)
  {
    Data bestPrv = segtree.query(0, h[i]);
    segtree.update(h[i], Data{max(a[i], bestPrv.value + a[i])});
  }
  return segtree.query(0, maxH).value;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &h[i]);
    h[n] = 0;

    lli sum = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      sum += a[i];
    }

    lli ans = solve3();
    printf("%lld\n", ans);
  }
  return 0;
}