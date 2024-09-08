#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  lli value;
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
Segtree<Data> countTree[2];
Segtree<Data> sumTree[2];

const int maxN = 1e6; int n, m;
int a[maxN];

int getSum(const vector<lli>& c)
{
  return c[0] + 2*c[1];
}

int binarySearch(int x, int k, int lo, int hi, bool upperBound)
{
  int llo = lo, hhi = hi;
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (countTree[k].query(mid, hhi).value >= x) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (countTree[k].query(llo, mid).value >= x) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      --a[i];
    }
    for (int j = 0; j < 2; ++j)
    {
      countTree[j] = Segtree<Data>(n, nil);
      sumTree[j] = Segtree<Data>(n, nil);
      for (int i = 0; i < n; ++i)
      {
        countTree[j].data[i].value = 0;
        sumTree[j].data[i].value = 0;
        countTree[j].data[i].value = a[i] == j;
        sumTree[j].data[i].value = a[i] == j ? i : 0;
      }
      countTree[j].build();
      sumTree[j].build();
    }

    lli ans = 0;
    for (int i = 0; i < m; ++i)
    {
      int x, y, z; scanf("%d %d %d", &x, &y, &z); --x, --y, --z;
      if (a[x] != y)
      {
        countTree[a[x]].update(x, Data{0});
        sumTree[a[x]].update(x, Data{0});
        a[x] = y;
        countTree[a[x]].update(x, Data{1});
        sumTree[a[x]].update(x, Data{x});
      }

      vector<lli> l = {countTree[0].query(0, z).value, countTree[1].query(0, z).value};
      vector<int> lrange = {0, z};
      vector<lli> r = {countTree[0].query(z + 1, n - 1).value, countTree[1].query(z + 1, n - 1).value};
      vector<int> rrange = {z + 1, n - 1};
      bool swapped = false;
      if (getSum(l) < getSum(r))
        swap(l, r), swapped = true;
      int delta = getSum(l) - getSum(r);
      int originalDelta = delta;
      int required = delta >> 1;

      lli now = 0;
      if (delta != 0 && (~delta & 1) && l[1] >= required && r[0] >= required)
      {
        lli toAdd;
        if (swapped)
        {
          int lp = binarySearch(required, 0, lrange[0], lrange[1], true);
          int rp = binarySearch(required, 1, rrange[0], rrange[1], false);
          toAdd = sumTree[1].query(rrange[0], rp).value - sumTree[0].query(lp, lrange[1]).value;
        }
        else
        {
          int lp = binarySearch(required, 1, lrange[0], lrange[1], true);
          int rp = binarySearch(required, 0, rrange[0], rrange[1], false);
          toAdd = sumTree[0].query(rrange[0], rp).value - sumTree[1].query(lp, lrange[1]).value;
        }
        now = toAdd;
        delta = 0;
      }

      if (delta != 0)
        now = -1;

      ans += now;
    }

    printf("Case #%d: %lld\n", testCase, ans);
  }
  return 0;
}
