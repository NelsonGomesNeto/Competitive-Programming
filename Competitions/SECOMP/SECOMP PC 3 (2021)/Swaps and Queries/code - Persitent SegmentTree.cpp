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
const SegNode nil = SegNode(0);

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
  void update2(int v, int pos, T value)
  {
    // changeTree.push_back(vector<int>());
    // changeTree[v].push_back(roots.size());
    // roots.push_back(update(pos, value, roots[v], 0, size - 1));
    update2(pos, value, roots[v], 0, size - 1);
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
  int update2(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      // value = st[i] + value;
      // st.push_back(value);
      st[i].value += value.value;
      // data[lo] = value;
      // return st.size() - 1;
      return i;
    }
    int mid = (lo + hi) >> 1, newRootIdx = st.size(), left = st[i].left, right = st[i].right;
    // st.push_back(T());
    if (pos <= mid) left = update2(pos, value, st[i].left, lo, mid);
    else right = update2(pos, value, st[i].right, mid + 1, hi);
    // st[newRootIdx] = st[left] + st[right];
    // st[newRootIdx].left = left, st[newRootIdx].right = right;
    st[i].value = st[left].value + st[right].value;
    // return newRootIdx;
    return i;
  }
};
PersistentSegTree<SegNode> segtree;

const int maxN = 1e5; int n, q;
int a[maxN];
vector<int> pos[maxN];
int valueToVersion[maxN];

int cntAbove(int mid, int x, int l, int r)
{
  return segtree.query(valueToVersion[mid], l, r).value - (x - 1 < 0 ? 0 : segtree.query(valueToVersion[x - 1], l, r).value);
}
int cntBelow(int mid, int x, int l, int r)
{
  return segtree.query(valueToVersion[x], l, r).value - (mid - 1 < 0 ? 0 : segtree.query(valueToVersion[mid - 1], l, r).value);
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
      valueToVersion[i] = i + 1;
    }

    segtree = PersistentSegTree<SegNode>(n, nil);
    segtree.build();

    for (int i = 0; i < n; i++) pos[i].clear();
    for (int i = 0; i < n; i++)
      pos[a[i]].push_back(i);
    for (int i = 0; i < n; i++)
      for (int p: pos[i])
        segtree.update(i, p, SegNode(1));

    scanf("%d", &q);
    for (int qq = 1; qq <= q; qq++)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int i, j; scanf("%d %d", &i, &j); i--, j--;
        // update
        segtree.update(valueToVersion[a[i]], i, SegNode(-1));
        // valueToVersion[a[i]] = segtree.roots.size() - 1;
        segtree.update(valueToVersion[a[i]], j, SegNode(1));
        // valueToVersion[a[i]] = segtree.roots.size() - 1;

        segtree.update(valueToVersion[a[j]], j, SegNode(-1));
        // valueToVersion[a[j]] = segtree.roots.size() - 1;
        segtree.update(valueToVersion[a[j]], i, SegNode(1));
        // valueToVersion[a[j]] = segtree.roots.size() - 1;

        swap(a[i], a[j]);
      }
      else
      {
        int l, r, x; scanf("%d %d %d", &l, &r, &x); l--, r--, x--;

        bool upperBound = op == 3;
        // query
        int lo = 0, hi = x;
        if (!upperBound) lo = x, hi = n - 1;
        while (lo < hi)
        {
          int mid = (lo + hi + upperBound) >> 1;
          if (upperBound)
          {
            printf("\t%d %d - %d - %d\n", lo, hi, mid, cntBelow(mid, x, l, r));
            if (cntBelow(mid, x, l, r) > 0) lo = mid;
            else hi = mid - 1;
          }
          else
          {
            printf("\t%d %d - %d - %d\n", lo, hi, mid, cntAbove(mid, x, l, r));
            if (cntAbove(mid, x, l, r) > 0) hi = mid;
            else lo = mid + 1;
          }
        }

        int ans = -1;
        if (!upperBound && cntAbove(lo, x, l, r) > 0) ans = lo + 1;
        if (upperBound && cntBelow(lo, x, l, r) > 0) ans = lo + 1;
        printf("%d\n", ans);
      }
    }
    printf("\t%d\n", segtree.query(valueToVersion[3], 0, 2).value);

    break;
  }
  return 0;
}
