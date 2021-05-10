#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  version[i] -> range[0 : i]
  value[i] -> seg.data[i] + 1
*/

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
  int greaterThanK(int k, int qlo, int qhi)
  {
    int r = query(qhi, k, size - 1).sum, l = query(qlo - 1, k, size - 1).sum;
    return r - l;
  }
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
  int update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st.push_back(st[i] + value);
      // data[lo] = value;
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

const int maxN = 2e5; int n;
int a[maxN];
vector<int> as;

void printAllVersions()
{
  int n = segtree.size;
  for (int i = 0; i < segtree.roots.size(); i++)
  {
    int root = segtree.roots[i];
    printf("\tVersion %d (root: %d): ", i, root);
    for (int j = 0; j < n; j++)
      printf("%d%c", segtree.query(i, j, j).sum, j < n - 1 ? ' ' : '\n');
  }
  // printf("\tChangeTree:\n");
  // printChangeTree();
}

int main()
{
  while (~scanf("%d", &n))
  {
    as.clear();
    as.push_back(-1);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      as.push_back(a[i]);
    }
    sort(as.begin(), as.end());
    as.resize(distance(as.begin(), unique(as.begin(), as.end())));

    for (int i = 0; i < n; i++)
      a[i] = lower_bound(as.begin(), as.end(), a[i]) - as.begin();
    DEBUG
      for (int i = 0; i < n; i++)
        printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');

    segtree = PersistentSegTree<SegNode>(as.size(), nil);
    for (int i = 0; i < as.size(); i++)
      segtree.data[i] = nil;
    segtree.build();

    for (int i = 0; i < n; i++)
      segtree.update(i, a[i], SegNode(1));

    DEBUG printAllVersions();

    int q; scanf("%d", &q);
    int ans = 0;
    for (int qq = 0; qq < q; qq++)
    {
      int lo, hi; lli k; scanf("%d %d %lld", &lo, &hi, &k);
      lo ^= ans, hi ^= ans, k ^= ans;
      if (lo < 1) lo = 1;
      if (hi > n) hi = n;

      if (lo > hi) ans = 0;
      else
      {
        auto it = upper_bound(as.begin(), as.end(), k);
        if (it == as.end()) ans = 0;
        else
        {
          int pos = it - as.begin();
          ans = segtree.greaterThanK(pos, lo, hi);
        }
      }
      printf("%d\n", ans);
    }
  }

  return 0;
}