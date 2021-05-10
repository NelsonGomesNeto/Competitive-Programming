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
      st.push_back(value);
      data[lo] = value;
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

void printChangeTree(int u = 0, int depth = 2)
{
  for (int i = 0; i < depth; i++) printf("\t");
  printf("%3d\n", u);

  for (int v: segtree.changeTree[u])
    printChangeTree(v, depth + 1);
}

void printAllVersions(int n)
{
  for (int i = 0; i < segtree.roots.size(); i++)
  {
    int root = segtree.roots[i];
    printf("\tVersion %d (root: %d): ", i, root);
    for (int j = 0; j < n; j++)
      printf("%d%c", segtree.query(i, j, j).value, j < n - 1 ? ' ' : '\n');
  }
  printf("\tChangeTree:\n");
  printChangeTree();
}

int main()
{
  int n;
  scanf("%d", &n);

  segtree = PersistentSegTree<SegNode>(n, nil);
  for (int i = 0; i < n; i++)
    scanf("%d", &segtree.data[i].value);
  segtree.build();

  DEBUG printAllVersions(n);

  char op[2];
  while (~scanf(" %s", op))
  {
    if (op[0] == 'U')
    {
      int version, pos, value; scanf("%d %d %d", &version, &pos, &value);
      assert(pos >= 0 && pos < n);
      assert(version >= 0 && version < segtree.roots.size());
      segtree.update(version, pos, SegNode(value));
      printf("UpdateV%d[%d] -> %d\n", pos, version, value);
    }
    else if (op[0] == 'Q')
    {
      int version, lo, hi; scanf("%d %d %d", &version, &lo, &hi);
      printf("QueryV%d[%d : %d] -> %d\n", version, lo, hi, segtree.query(version, lo, hi).value);
    }

    DEBUG printAllVersions(n);
  }
  return 0;
}