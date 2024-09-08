#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  version[i] -> range[1 : i] (add an null update just to ensure (lo - 1) >= 0)
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
  // k, lo and hi are 1-indexed!!!!
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
vector<int> tree[maxN];

vector<int> eulerTour, eulerDelta;
int in[maxN], out[maxN];
int level[maxN];
void dfs(int u = 0, int depth = 0, int prv = -1)
{
  DEBUG printf("\t%d %d\n", u + 1, depth);
  level[u] = depth;
  in[u] = eulerTour.size();
  eulerTour.push_back(u);
  eulerDelta.push_back(depth);

  for (int v: tree[u])
    if (v != prv)
      dfs(v, depth + 1, u);

  out[u] = eulerTour.size();
  eulerTour.push_back(u);
  eulerDelta.push_back(depth);
}

void printAllVersions(int n)
{
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
    for (int i = 0; i < n; i++) tree[i].clear();
    eulerTour.clear(), eulerDelta.clear();
    for (int i = 1; i < n; i++)
    {
      int p; scanf("%d", &p); p--;
      tree[i].push_back(p), tree[p].push_back(i);
    }

    dfs();

    assert(2*n == eulerDelta.size());

    segtree = PersistentSegTree<SegNode>(n, nil);
    for (int i = 0; i < n; i++)
      segtree.data[i] = nil;
    segtree.build();

    for (int i = 0; i < 2*n; i++)
      segtree.update(i, eulerDelta[i], SegNode(1));

    DEBUG {
      for (int i = 0; i < 2*n; i++)
        printf("\t\t%d (%d, %d) %d\n", eulerTour[i] + 1, in[eulerTour[i]], out[eulerTour[i]], eulerDelta[i]);
      printAllVersions(n);
    }

    int q; scanf("%d", &q);
    while (q--)
    {
      int u, d; scanf("%d %d", &u, &d); u--;
      // d += level[u];

      // count subtree eulerDelta == d
      int a = segtree.query(in[u], d, d).sum;
      int b = segtree.query(out[u] + 1, d, d).sum;
      int ans = (b - a) / 2;
      DEBUG printf("\t%d %d\n", a, b);
      printf("%d\n", ans);
    }
  }
  return 0;
}