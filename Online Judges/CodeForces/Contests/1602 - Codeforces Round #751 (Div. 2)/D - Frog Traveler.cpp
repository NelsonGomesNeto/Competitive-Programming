#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int pos, fall;
  Data operator+(const Data &other)
  {
    if (fall < other.fall) return *this;
    else if (fall == other.fall) return Data{min(pos, other.pos), fall};
    else return other;
  }
};
const Data nil = Data{INT_MAX, INT_MAX};

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

const int maxN = 3e5; int n;
int a[maxN], b[maxN];
int visited[maxN];
vector<int> ans;

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);

    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
    {
      segtree.data[i] = Data{i, i + b[i]};
      visited[i] = 0;
    }
    segtree.build();

    int at = n - 1;
    ans.clear();
    while (at >= 0)
    {
      DEBUG printf("%d - %d\n", at, a[at]);
      if (at - a[at] < 0)
      {
        ans.push_back(0);
        at -= a[at];
      }
      else if (a[at] == 0)
      {
        at -= b[at];
      }
      else
      {
        Data furthest = segtree.query(max(0, at - a[at]), at - 1);
        DEBUG printf("\t%d %d\n", furthest.pos, furthest.fall);
        ans.push_back(furthest.pos + 1);
        at = furthest.fall;
      }

      if (++visited[at] == 5) break;
    }

    if (at >= 0) printf("-1\n");
    else
    {
      printf("%d\n", (int)ans.size());
      for (int i = 0; i < ans.size(); i++)
        printf("%d%c", ans[i], i + 1 < ans.size() ? ' ' : '\n');
    }
  }
  return 0;
}
