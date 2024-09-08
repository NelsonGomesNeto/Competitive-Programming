#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
int a[maxN];
lli acc[maxN + 1];

const lli inf = 1e18;
struct Data
{
  lli minimum, maximum;
  Data operator+(const Data &other)
  {
    return Data{min(minimum, other.minimum), max(maximum, other.maximum)};
  }
};
const Data nil = Data{inf, -inf};

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

struct Block
{
  lli sum; int lo, hi;
  bool operator<(const Block &other) const { return sum < other.sum; }
};
vector<Block> blocks;
pair<int, pair<lli, lli>> split(int lo, int hi, int mid)
{
  vector<lli> left, right;
  for (int i = lo; i <= hi; i++)
    if (a[i] <= mid)
      left.push_back(a[i]);
    else
      right.push_back(a[i]);

  lli leftSum = 0, rightSum = 0;
  for (int i = 0; i < left.size(); i++)
  {
    a[lo + i] = left[i];
    segtree.update(lo + i, Data{a[lo + i], a[lo + i]});
    leftSum += a[lo + i];
  }
  for (int i = 0; i < right.size(); i++)
  {
    a[lo + left.size() + i] = right[i];
    segtree.update(lo + left.size() + i, Data{a[lo + left.size() + i], a[lo + left.size() + i]});
    rightSum += a[lo + left.size() + i];
  }

  return make_pair(left.size(), make_pair(leftSum, rightSum));
}
void build(int lo = 0, int hi = n - 1, lli sum = acc[n])
{
  blocks.push_back(Block{sum, lo, hi});
  Data now = segtree.query(lo, hi);

  if (now.minimum == now.maximum) return;
  lli mid = (now.minimum + now.maximum) >> 1LL;

  auto res = split(lo, hi, mid);
  int base = res.first;
  lli leftSum = res.second.first, rightSum = res.second.second;
  build(lo, lo + base - 1, leftSum);
  build(lo + base, hi, rightSum);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + a[i];

    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
      segtree.data[i] = Data{a[i], a[i]};
    segtree.build();

    blocks.clear();
    build();
    // sort(blocks.begin(), blocks.end());
    set<lli> has;
    for (Block &b: blocks)
      has.insert(b.sum);

    while (q--)
    {
      lli s; scanf("%lld", &s);
      bool can = has.count(s);
      printf("%s\n", can ? "YES" : "NO");
    }

    DEBUG printf("\n");
  }
  return 0;
}
