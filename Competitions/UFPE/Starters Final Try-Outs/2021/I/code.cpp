#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int value;
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
      // st[i] = data[lo] = value;
      st[i].value += value.value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

const int maxN = 1e5; int n, q;
vector<lli> xs;
lli a[maxN];

struct Query
{
  int op, id; lli x; lli k;
};
Query queries[maxN];

int main()
{
  while (~scanf("%d %d", &q, &n))
  {
    memset(a, 0, sizeof(a));

    xs.clear();
    xs.push_back(0);
    for (int i = 0; i < q; i++)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int id; lli x; scanf("%d %lld", &id, &x);
        a[id] += x;
        xs.push_back(a[id]);
        queries[i] = Query{op, id, x, -1};
      }
      else
      {
        lli k; scanf("%lld", &k);
        xs.push_back(k);
        queries[i] = Query{op, -1, -1, k};
      }
    }

    sort(xs.begin(), xs.end());
    xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));

    segtree = Segtree<Data>(xs.size(), nil);
    for (int i = 0; i < xs.size(); i++) segtree.data[i] = nil;
    segtree.data[0] = Data{n};
    segtree.build();

    memset(a, 0, sizeof(a));
    for (int i = 0; i < q; i++)
    {
      Query q = queries[i];
      if (q.op == 1)
      {
        int pos = lower_bound(xs.begin(), xs.end(), a[q.id]) - xs.begin();
        segtree.update(pos, Data{-1});
        a[q.id] += q.x;
        pos = lower_bound(xs.begin(), xs.end(), a[q.id]) - xs.begin();
        segtree.update(pos, Data{1});
      }
      else
      {
        int pos = lower_bound(xs.begin(), xs.end(), q.k) - xs.begin();
        if (pos == xs.size() - 1) printf("0\n");
        else printf("%d\n", segtree.query(pos + 1, xs.size() - 1).value);
      }
    }
  }
  return 0;
}