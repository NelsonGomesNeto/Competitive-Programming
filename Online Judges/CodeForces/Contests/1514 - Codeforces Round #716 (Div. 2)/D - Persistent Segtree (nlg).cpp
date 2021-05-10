#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, q;
vector<int> pos[maxN + 1];
int a[maxN];

int cntInRange(int v, int l, int r)
{
  if (v == -1) return -1;
  return upper_bound(pos[v].begin(), pos[v].end(), r) - lower_bound(pos[v].begin(), pos[v].end(), l);
}

struct SegNode
{
  int left = -1, right = -1;

  int sum;
  SegNode() { }
  SegNode(int sum) : sum(sum) { }
  SegNode operator+(const SegNode &other)
  {
    return SegNode{sum + other.sum};
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
  int kthSmallest(int k, int qlo, int qhi) { return kthSmallest(k, roots[qlo - 1], roots[qhi], 0, size - 1); }
  void update(int v, int pos, T value)
  {
    // changeTree.push_back(vector<int>());
    // changeTree[v].push_back(roots.size());
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
  int kthSmallest(int k, int l, int r, int lo, int hi)
  {
    if (lo == hi) return lo;
    int mid = (lo + hi) >> 1;
    int curr = st[st[r].left].sum - st[st[l].left].sum;
    if (curr >= k) return kthSmallest(k, st[l].left, st[r].left, lo, mid);
    return kthSmallest(k - curr, st[l].right, st[r].right, mid + 1, hi);
  }
  int update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st.push_back(st[i] + value);
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

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    for (int i = 0; i <= n; i++) pos[i].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      pos[a[i]].push_back(i);
    }
    
    PersistentSegTree<SegNode> segtree = PersistentSegTree<SegNode>(n + 1, nil);
    for (int i = 0; i <= n; i++)
      segtree.data[i] = nil;
    segtree.build();

    for (int i = 0; i < n; i++)
      segtree.update(i, a[i], SegNode(1));

    DEBUG
      for (int i = 0; i < n; i++)
        printf("\t\t%d - %d\n", i, segtree.kthSmallest(i + 1, 1, n));

    for (int i = 0; i < q; i++)
    {
      int l, r; scanf("%d %d", &l, &r); l--, r--;

      int mostRep = segtree.kthSmallest((r - l + 1) >> 1, l + 1, r + 1);
      DEBUG printf("\t[%d, %d]: %d\n", l + 1, r + 1, mostRep);
      int freq = cntInRange(mostRep, l, r);

      DEBUG printf("\t%d %d\n", mostRep, freq);
      printf("%d\n", max(1, freq - (r - l + 1 - freq)));
    }
  }
  return 0;
}