#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  lli value, cnt;
  Data operator+(const Data &other)
  {
    return Data{value + other.value, cnt + other.cnt};
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

const int maxN = 3e5; int n;
lli a[maxN];
vector<int> as;
int aPos(lli value)
{
  return lower_bound(as.begin(), as.end(), value) - as.begin();
}

lli ans[maxN];

lli calcDelta(int i)
{
  if (i < 0 || i >= n) return LONG_LONG_MIN;

  lli delta = 0;
  int p = aPos(a[i]);

  if (p)
  {
    Data l = segtree.query(0, p - 1);
    delta += a[i]*l.cnt - l.value;
  }

  if (p + 1 < n)
  {
    Data r = segtree.query(p + 1, as.size() - 1);
    delta += r.value - a[i]*r.cnt;
  }

  return delta;
}

void applyDelta(int i)
{
  segtree.update(aPos(a[i]), Data{a[i], 1});
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    sort(a, a+n);

    as.clear();
    for (int i = 0; i < n; i++) as.push_back(a[i]);
    sort(as.begin(), as.end());
    as.resize(distance(as.begin(), unique(as.begin(), as.end())));

    segtree = Segtree<Data>(as.size(), nil);

    lli curr = ans[0] = a[n - 1] - a[0];
    int lo = 0, hi = n - 1;
    applyDelta(lo);
    applyDelta(hi);
    for (int i = 1; lo < hi; i++)
    {
      lli deltaLeft = calcDelta(lo + 1);
      lli deltaRight = calcDelta(hi - 1);
      if (deltaLeft > deltaRight)
      {
        lo++, curr += deltaLeft;
        applyDelta(lo);
      }
      else
      {
        hi--, curr += deltaRight;
        applyDelta(hi);
      }
      ans[i] = curr;
    }

    for (int i = 0; i + 1 < n; i++)
      printf("%lld%c", ans[i], i + 2 < n ? ' ' : '\n');
  }
  return 0;
}