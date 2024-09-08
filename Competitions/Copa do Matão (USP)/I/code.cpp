#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct SegNode
{
  int left = -1, right = -1;
  lli sum;
  SegNode() { }
  SegNode(lli sum) : sum(sum) { }
  SegNode operator+(const SegNode &other)
  {
    return SegNode{sum + other.sum};
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
  lli maxSmallestSum(lli d, int qlo, int qhi) { return maxSmallestSum(0, d, roots[qlo - 1], roots[qhi], 0, size - 1); }
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
  lli maxSmallestSum(lli currSum, lli d, int l, int r, int lo, int hi)
  {
    lli rem = st[r].sum - st[l].sum;
    DEBUG printf("\t%lld %lld %lld %lld - %d %d - %d %d\n", currSum, d, 0LL, rem, l, r, lo, hi);
    if (lo == hi)
    {
      if (currSum + rem <= d) return currSum + rem;
      return currSum;
    }
    int mid = (lo + hi) >> 1;
    lli sum = st[st[r].left].sum - st[st[l].left].sum;
    if (sum > d) return maxSmallestSum(currSum, d, st[l].left, st[r].left, lo, mid);
    else return maxSmallestSum(currSum + sum, d - sum, st[l].right, st[r].right, mid + 1, hi);
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
lli a[maxN];
vector<lli> as;

lli getSum(int lo, int hi, int x)
{
  return segtree.query(hi, 0, x).sum - segtree.query(lo - 1, 0, x).sum;
}

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    as.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      as.push_back(a[i]);
    }
    sort(as.begin(), as.end());
    as.resize(distance(as.begin(), unique(as.begin(), as.end())));

    segtree = PersistentSegTree<SegNode>(as.size(), nil);
    for (int i = 0; i < as.size(); i++)
    {
      // printf("\t%lld\n", as[i]);
      segtree.data[i] = nil;
    }
    segtree.build();
    for (int i = 0; i < n; i++)
    {
      int pos = lower_bound(as.begin(), as.end(), a[i]) - as.begin();
      segtree.update(i, pos, SegNode(a[i]));
    }

    DEBUG printf("\tlol: %lld\n", segtree.query(3, 2, 2).sum);

    lli prvAns = 0;
    for (int qq = 0; qq < q; qq++)
    {
      int x, y; lli z; scanf("%d %d %lld", &x, &y, &z);
      int l = 1 + (x + prvAns - 1) % n;
      int r = 1 + (y + prvAns - 1) % n;
      lli d = z + prvAns;
      DEBUG printf("\t\t%d %d %lld\n", l, r, d);

      // lli ans = max(0LL, segtree.maxSmallestSum(d, l, r));
      int lo = 0, hi = as.size() - 1;
      while (lo < hi)
      {
        int mid = (lo + hi + 1) >> 1;
        if (getSum(l, r, mid) <= d) lo = mid;
        else hi = mid - 1;
      }
      lli ans = getSum(l, r, lo);
      if (ans > d) ans = 0;

      printf("%lld\n", ans);
      prvAns = ans;
    }
  }

  return 0;
}