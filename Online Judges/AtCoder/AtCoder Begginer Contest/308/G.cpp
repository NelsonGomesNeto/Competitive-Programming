#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = 1e12;
struct Data
{
  int cnt;
  lli value;
  lli left, right;
  lli minXor;
  Data operator+(const Data &other)
  {
    if (cnt <= 0) return other;
    if (other.cnt <= 0) return *this;
    if (cnt >= 2) return Data{2, -1, -1, -1, 0};
    if (other.cnt >= 2) return Data{2, -1, -1, -1, 0};

    lli res = min(minXor, other.minXor);
    if (value != -1 && other.value != -1)
      return Data{1, -1, value, other.value, min(res, value ^ other.value)};

    if (value != -1 && other.left != -1)
      return Data{1, -1, value, other.right, min(res, value ^ other.left)};

    if (right != -1 && other.value != -1)
      return Data{1, -1, left, other.value, min(res, right ^ other.value)};

    if (right != -1 && other.left != -1)
      return Data{1, -1, left, other.right, min(res, right ^ other.left)};

    return Data{-1, -1, -1, -1, inf};
  }
};
const Data nil = Data{-1, -1, -1, -1, inf};

// DON'T FORGET TO DEFINE THE NIL!!!
template <class T>
struct Segtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  Segtree() {}
  Segtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size);
    st.resize(4 * size);
  }
  Segtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4 * size);
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
    build(2 * i, lo, mid), build(2 * i + 1, mid + 1, hi);
    st[i] = st[2 * i] + st[2 * i + 1];
  }
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi)
      return nil;
    if (lo >= qlo && hi <= qhi)
      return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2 * i, lo, mid) + query(qlo, qhi, 2 * i + 1, mid + 1, hi);
  }
  void update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i].cnt += value.cnt;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid)
      update(pos, value, 2 * i, lo, mid);
    else
      update(pos, value, 2 * i + 1, mid + 1, hi);
    st[i] = st[2 * i] + st[2 * i + 1];
  }
};
Segtree<Data> segtree;

const int maxQ = 3e5;
int tq;
vector<lli> xs;

struct Query
{
  int op;
  lli x;
  void read()
  {
    scanf("%d", &op);
    if (op != 3)
    {
      scanf("%lld", &x);
      xs.push_back(x);
    }
  }
};
vector<Query> queries;
int getXPos(lli x)
{
  return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}

int main()
{
  while (~scanf("%d", &tq))
  {
    xs.clear();
    queries.clear();
    queries.resize(tq);
    for (Query& q : queries)
      q.read();

    sort(xs.begin(), xs.end());
    xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));

    segtree = Segtree<Data>(xs.size(), nil);
    for (int i = 0; i < xs.size(); ++i)
      segtree.data[i] = Data{0, xs[i], -1, -1, inf};
    segtree.build();

    for (const Query& q : queries)
    {
      if (q.op == 1)
      {
        int pos = getXPos(q.x);
        segtree.update(pos, Data{1});
      }
      else if (q.op == 2)
      {
        int pos = getXPos(q.x);
        segtree.update(pos, Data{-1});
      }
      else // 3
      {
        Data ans = segtree.query(0, xs.size() - 1);
        // assert(ans.minXor != inf);
        printf("%lld\n", ans.minXor);
      }
    }
  }
  return 0;
}
