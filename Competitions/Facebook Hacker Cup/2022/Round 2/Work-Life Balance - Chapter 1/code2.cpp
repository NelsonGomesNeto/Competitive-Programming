#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int value[3];
  int sum() const { return value[0] + 2*value[1] + 3*value[2]; }
  Data operator+(const Data &other)
  {
    Data res;
    for (int i = 0; i < 3; ++i)
      res.value[i] = value[i] + other.value[i];
    return res;
  }
};
const Data nil = Data{0, 0, 0}, up[3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

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

const int maxN = 1e6; int n, m;
int a[maxN];

bool hasMoves(const int delta, const Data& l, const Data& r)
{
  for (int i = 3; i >= 2; --i)
    for (int j = 1; j < i; ++j)
      if (l.value[i-1] && r.value[j-1] && (delta - 2*i + 2*j) >= 0)
        return true;
  return false;
}

void applyMove(int& delta, Data& l, Data& r)
{
  for (int i = 3; i >= 2; --i)
    for (int j = 1; j < i; ++j)
      if (l.value[i-1] && r.value[j-1] && (delta - 2*i + 2*j) >= 0)
      {
        --l.value[i-1], --r.value[j-1];
        ++l.value[j-1], ++r.value[i-1];
        delta += -2*i + 2*j;
        return;
      }
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
    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; ++i)
    {
      segtree.data[i] = nil;
      segtree.data[i].value[a[i]] = 1;
    }
    segtree.build();

    lli ans = 0;
    for (int i = 0; i < m; ++i)
    {
      int x, y, z; scanf("%d %d %d", &x, &y, &z); --x, --y, --z;
      a[x] = y;
      segtree.update(x, up[y]);

      Data l = segtree.query(0, z);
      Data r = segtree.query(z + 1, n - 1);
      if (l.sum() < r.sum())
        swap(l, r);
      int delta = l.sum() - r.sum();

      lli now = 0;
      DEBUG printf("\t\t%d %d\n", l.sum(), r.sum());
      for (int i = 3; i >= 2 && delta != 0; --i)
        for (int j = 1; j < i && delta != 0; ++j)
          while (l.value[i-1] && r.value[j-1] && (delta - 2*i + 2*j) >= 0)
          {
            int has = min(l.value[i-1], r.value[j-1]);
            int lo = 0, hi = has;
            while (lo < hi)
            {
              int mid = (lo + hi + 1) >> 1;
              if ((delta - 2*i*mid + 2*j*mid) >= 0) lo = mid;
              else hi = mid - 1;
            }
            l.value[i-1] -= lo, r.value[j-1] -= lo;
            l.value[j-1] += lo, r.value[i-1] += lo;
            delta += -2*i*lo + 2*j*lo;
            now += lo;
          }
        DEBUG printf("\t\t%d %d\n", l.sum(), r.sum());

      if (delta != 0)
        now = -1;

      DEBUG printf("\t%d - %d\n", i, now);

      ans += now;
    }

    printf("Case #%d: %lld\n", testCase, ans);
  }
  return 0;
}
