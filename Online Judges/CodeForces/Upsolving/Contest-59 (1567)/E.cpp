#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = 1e18;

// 2 - 3
// 3 - 6
// 4 - 10
// 5 - 15
lli comb(lli x)
{
  return x * (x + 1) >> 1;
}

struct Data
{
  lli leftMin, leftMax, rightMin, rightMax; bool full; lli leftSize, rightSize, ans;
  Data operator+(const Data &other)
  {
    if (other.leftMax == inf) return *this;
    if (leftMax == inf) return other;

    if (rightMax <= other.leftMin)
    {
      if (full && other.full)
      {
        lli newSize = leftSize + other.rightSize;
        return Data{leftMin, other.rightMax, leftMin, other.rightMax, true, newSize, newSize, comb(newSize)};
      }
      else if (full && !other.full)
      {
        lli newSize = leftSize + other.leftSize;
        return Data{leftMin, other.leftMax, other.rightMin, other.rightMax, false, newSize, other.rightSize, comb(newSize) + other.ans - comb(other.leftSize)};
      }
      else if (!full & other.full)
      {
        lli newSize = rightSize + other.rightSize;
        return Data{leftMin, leftMax, rightMin, other.rightMax, false, leftSize, newSize, comb(newSize) + ans - comb(rightSize)};
      }
      else if (!full && !other.full)
      {
        lli newSize = rightSize + other.leftSize;
        return Data{leftMin, leftMax, other.rightMin, other.rightMax, false, leftSize, other.rightSize, comb(newSize) + ans + other.ans - comb(rightSize) - comb(other.leftSize)};
      }
    }
    return Data{leftMin, leftMax, other.rightMin, other.rightMax, false, leftSize, other.rightSize, ans + other.ans};
  }
};
const Data nil = Data{-inf, inf, -inf, inf, false, 0, 0, 0};

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
    // T l = query(qlo, qhi, 2*i, lo, mid);
    // T r = query(qlo, qhi, 2*i + 1, mid + 1, hi);
    // T res = l + r;
    // printf("%d %d:\n", lo, hi);
    // printf("\t%lld %lld - %lld %lld - %d - %lld %lld - %lld\n", l.leftMin, l.leftMax, l.rightMin, l.rightMax, l.full, l.leftSize, l.rightSize, l.ans);
    // printf("\t%lld %lld - %lld %lld - %d - %lld %lld - %lld\n", r.leftMin, r.leftMax, r.rightMin, r.rightMax, r.full, r.leftSize, r.rightSize, r.ans);
    // printf("\t%lld %lld - %lld %lld - %d - %lld %lld - %lld\n", res.leftMin, res.leftMax, res.rightMin, res.rightMax, res.full, res.leftSize, res.rightSize, res.ans);
    // return res;
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

const int maxN = 2e5; int n, q;
lli a[maxN];

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      segtree.data[i] = Data{a[i], a[i], a[i], a[i], true, 1, 1, 1};
    }
    segtree.build();

    for (int i = 0; i < q; i++)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int x; lli y; scanf("%d %lld", &x, &y); x--;
        segtree.update(x, Data{y, y, y, y, true, 1, 1, 1});
      }
      else
      {
        int l, r; scanf("%d %d", &l, &r); l--, r--;
        printf("%lld\n", segtree.query(l, r).ans);
      }
    }
  }
  return 0;
}
