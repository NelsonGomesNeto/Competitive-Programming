#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  lli minimum, maximum;
  Data operator+(const Data &other)
  {
    return Data{min(minimum, other.minimum), max(maximum, other.maximum)};
  }
};
const Data nil = Data{(lli)1e18, (lli)-1e18};

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

const int maxN = 2e5; int n;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  bool operator<(const Point &other) const { return x < other.x; }
};
Point points[maxN];

int binarySearch(lli target, bool upperBound)
{
  int lo = 0, hi = n - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (points[mid].x <= target) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (points[mid].x >= target) hi = mid;
      else lo = mid + 1;
    }
  }
  if (upperBound) return points[lo].x <= target ? lo : -1;
  return points[lo].x >= target ? lo : -1;
}
lli dist(int i, lli dx)
{
  lli best = 0;
  int leftPos = binarySearch(points[i].x - dx, true);
  if (leftPos != -1)
  {
    Data res = segtree.query(0, leftPos);
    best = max({best, abs(points[i].y - res.minimum), abs(points[i].y - res.maximum)});
  }
  int rightPos = binarySearch(points[i].x + dx, false);
  if (rightPos != -1)
  {
    Data res = segtree.query(rightPos, n - 1);
    best = max({best, abs(points[i].y - res.minimum), abs(points[i].y - res.maximum)});
  }
  return best;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      points[i].read();

    sort(points, points+n);
    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
      segtree.data[i] = Data{points[i].y, points[i].y};
    segtree.build();

    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      lli lo = 0, hi = 1e9;
      while (lo < hi)
      {
        lli mid = (lo + hi + 1) >> 1LL;
        if (dist(i, mid) >= mid) lo = mid;
        else hi = mid - 1;
      }
      ans = max(ans, lo);
    }
    printf("%lld\n", ans);
  }
  return 0;
}