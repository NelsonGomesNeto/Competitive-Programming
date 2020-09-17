#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  (I will index everything be 0)
  If you figure out how to solve this problem online: text me

  Here is the offline solution

  A mind blowing shift in perspective:
    set a[i] to i - a[i] + 1
    Now, a[i] == 0: removable
    And after removing: just subtract 1 from i to n - 1
    NICE, NICE, NICE

  Now, we just need to go from right to left aplying the game's rule:
    find the rightMost 0 (I've used lazyly used a LazySegtree for this)
    subtract 1 from every number after it

    Now for each query with x == currentPosition:
      ans[queryPos] = addAmoutOfRemovedFrom(x to y)

      Notice that you can calculate that using a BIT ou Segtree
      Set it all to 0 and add 1 at the position of removed number
*/

const int maxN = 3e5; int n, q;
int a[maxN];

struct RightMostMin
{
  int minimum, position;
  RightMostMin operator+(const RightMostMin &other)
  {
    if (minimum < other.minimum)
      return *this;
    return other;
  }
};
const RightMostMin nilRightMostMin = RightMostMin{(int)1e6, 0};

template<class T>
struct LazySegtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  vector<T> lazy;
  vector<int> pending;
  LazySegtree() { }
  LazySegtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size);
    st.resize(4*size);
    lazy.resize(4*size);
    pending.resize(4*size);
  }
  LazySegtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    lazy.resize(4*size);
    pending.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
  void update(int op, int ulo, int uhi, T value) { update(op, ulo, uhi, value, 1, 0, size - 1); }
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
  void lazyUpdate(int i, int lo, int hi)
  {
    if (pending[i])
    {
      st[i].minimum -= lazy[i].minimum;
      if (lo != hi)
      {
        lazy[2*i].minimum += lazy[i].minimum;
        lazy[2*i + 1].minimum += lazy[i].minimum;
        pending[2*i] = pending[2*i + 1] = pending[i];
      }
      lazy[i] = RightMostMin{0, 0}, pending[i] = 0;
    }
  }
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    lazyUpdate(i, lo, hi);
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
  void update(int op, int ulo, int uhi, T &value, int i, int lo, int hi)
  {
    lazyUpdate(i, lo, hi);
    if (hi < ulo || lo > uhi) return;
    if (lo >= ulo && hi <= uhi)
    {
      lazy[i].minimum += value.minimum, pending[i] = op;
      lazyUpdate(i, lo, hi);
      return;
    }
    int mid = (lo + hi) >> 1;
    update(op, ulo, uhi, value, 2*i, lo, mid), update(op, ulo, uhi, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
LazySegtree<RightMostMin> lazySegtree;

struct Sum
{
  int value;
  Sum operator+(const Sum &other)
  {
    return Sum{value + other.value};
  }
};
const Sum nilSum = Sum{0};

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
Segtree<Sum> segtree;

vector<pair<int, int>> queries[maxN];
int ans[maxN];

int main()
{
  int tt = 0;
  while (scanf("%d %d", &n, &q) != EOF)
  {
    if (tt++) printf("\n");

    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i] = i - a[i] + 1;
      if (a[i] < 0) a[i] = 1e6;
    }

    for (int i = 0; i < n; i++) queries[i].clear();
    for (int i = 0; i < q; i++)
    {
      int x, y; scanf("%d %d", &x, &y);
      queries[x].push_back({y, i});
    }

    lazySegtree = LazySegtree<RightMostMin>(n, nilRightMostMin);
    for (int i = 0; i < n; i++)
      lazySegtree.data[i] = RightMostMin{a[i], i};
    lazySegtree.build();
    
    segtree = Segtree<Sum>(n, nilSum);
    for (int i = 0; i < n; i++) segtree.data[i].value = 0;
    segtree.build();

    for (int i = n - 1; i >= 0; i--)
    {
      while (true)
      {
        RightMostMin now = lazySegtree.query(i, n - 1);
        if (now.minimum != 0) break;

        lazySegtree.update(1, now.position, now.position, RightMostMin{(int)-1e6, 0});
        lazySegtree.update(1, now.position + 1, n - 1, RightMostMin{1, 0});

        segtree.update(now.position, Sum{1});
      }

      for (auto &yp: queries[i])
        ans[yp.second] = segtree.query(i, n - 1 - yp.first).value;
    }

    DEBUG
    {
      for (int i = 0; i < n; i++)
        printf("%3d%c", i, i < n - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i++)
        printf("%3d%c", a[i] == 1e6 ? 999 : a[i], i < n - 1 ? ' ' : '\n');
    }

    for (int i = 0; i < q; i++)
      printf("%d\n", ans[i]);
  }
  return 0;
}