#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct SegNode
{
  int left = -1, right = -1;
  int value;
  SegNode() { }
  SegNode(int value) : value(value) { }
  SegNode operator+(const SegNode &other)
  {
    return SegNode{value + other.value};
  }
};
const SegNode nil = SegNode{0};

// DON'T FORGET TO DEFINE THE NIL!!!
// YOU MIGHT WANT TO DISABLE CHANGE TREE!!!
template<class T>
struct PersistentSegTree
{
  int size;
  T nil;
  vector<int> roots;
  vector<vector<int>> changeTree;
  vector<T> data;
  vector<T> st;

  PersistentSegTree() { }
  PersistentSegTree(int size, T nil) : size(size), nil(nil)
  {
    roots.clear(), changeTree.clear(), st.clear();
    changeTree.resize(1);
    data.clear();
    data.resize(size);
  }
  PersistentSegTree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    roots.clear(), changeTree.clear(), st.clear();
    changeTree.resize(1);
    build();
  }
  void build() { roots.push_back(build(0, size - 1)); }
  T query(int v, int qlo, int qhi) { return query(qlo, qhi, roots[v], 0, size - 1); }
  void update(int v, int pos, T value)
  {
    changeTree.push_back(vector<int>());
    changeTree[v].push_back(roots.size());
    roots.push_back(update(pos, value, roots[v], 0, size - 1));
  }
  int build(int lo, int hi)
  {
    if (lo == hi)
    {
      st.push_back(data[lo]);
      return st.size() - 1;
    }
    int mid = (lo + hi) >> 1, newRootIdx = st.size();
    st.push_back(T());
    int left = build(lo, mid), right = build(mid + 1, hi);
    st[newRootIdx] = st[left] + st[right];
    st[newRootIdx].left = left, st[newRootIdx].right = right;
    return newRootIdx;
  }
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, st[i].left, lo, mid) + query(qlo, qhi, st[i].right, mid + 1, hi);
  }
  int update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st.push_back(st[i] + value);
      data[lo] = data[lo] + value;
      return st.size() - 1;
    }
    int mid = (lo + hi) >> 1, newRootIdx = st.size(), left = st[i].left, right = st[i].right;
    st.push_back(T());
    if (pos <= mid) left = update(pos, value, st[i].left, lo, mid);
    else right = update(pos, value, st[i].right, mid + 1, hi);
    st[newRootIdx] = st[left] + st[right];
    st[newRootIdx].left = left, st[newRootIdx].right = right;
    return newRootIdx;
  }
};
PersistentSegTree<SegNode> segtree;

const int maxN = 1e5; int n, q;
vector<int> a;

int main()
{
  while (~scanf("%d", &n))
  {
    a.resize(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    segtree = PersistentSegTree<SegNode>(n, nil);
    for (int i = 0; i < n; i++)
      segtree.data[i] = SegNode(a[i]);
    segtree.build();

    int q; scanf("%d", &q);
    while (q--)
    {
      int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
      if (a == 1)
        segtree.update(b, c - 1, SegNode(d));
      else
        printf("%d\n", segtree.query(b, c - 1, d - 1).value);
    }
  }
  return 0;
}