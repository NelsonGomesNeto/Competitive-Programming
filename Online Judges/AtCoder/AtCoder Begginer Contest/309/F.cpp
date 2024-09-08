#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = 1e9;
struct SegNode
{
  int left = -1, right = -1;
  int value;
  SegNode() {}
  SegNode(int value) : value(value) {}
  SegNode operator+(const SegNode &other)
  {
    return SegNode{min(value, other.value)};
  }
};
const SegNode nil = SegNode{inf};

// DON'T FORGET TO DEFINE THE NIL!!!
// YOU MIGHT WANT TO DISABLE CHANGE TREE!!!
template <class T>
struct PersistentSegTree
{
  int size;
  T nil;
  vector<int> roots;
  vector<vector<int>> changeTree;
  vector<T> data;
  vector<T> st;

  PersistentSegTree() {}
  PersistentSegTree(int size, T nil) : size(size), nil(nil)
  {
    roots.clear(), changeTree.clear(), st.clear();
    changeTree.resize(1);
    data.clear();
    data.resize(size, nil);
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
    if (hi < qlo || lo > qhi)
      return nil;
    if (lo >= qlo && hi <= qhi)
      return st[i];
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
    if (pos <= mid)
      left = update(pos, value, st[i].left, lo, mid);
    else
      right = update(pos, value, st[i].right, mid + 1, hi);
    st[newRootIdx] = st[left] + st[right];
    st[newRootIdx].left = left, st[newRootIdx].right = right;
    return newRootIdx;
  }
};
PersistentSegTree<SegNode> seg;

const int maxN = 2e5;
int n;
vector<int> originalBox[maxN];
vector<vector<int>> box;
vector<int> values;

void addBoxes(const vector<int>& permutation)
{
  for (int i = 0; i < n; ++i)
  {
    box.push_back(vector<int>(3));
    for (int j = 0; j < 3; ++j)
      box.back()[j] = originalBox[i][permutation[j]];
  }
}

bool bigger(const vector<int> &a, const vector<int> &b, const vector<int> &p1, const vector<int> &p2)
{
  return a[p1[0]] > b[p2[0]]
      && a[p1[1]] > b[p2[1]]
      && a[p1[2]] > b[p2[2]];
}

int main()
{
  while (~scanf("%d", &n))
  {
    box.clear();
    values.clear();
    for (int i = 0; i < n; ++i)
    {
      originalBox[i].clear();
      originalBox[i].resize(3);
      for (auto &a : originalBox[i])
      {
        scanf("%d", &a);
        values.push_back(a);
      }
    }
    sort(values.begin(), values.end());
    values.resize(distance(values.begin(), unique(values.begin(), values.end())));
    for (int i = 0; i < n; ++i)
      for (auto &a : originalBox[i])
        a = lower_bound(values.begin(), values.end(), a) - values.begin();

    bool ans = false;
    vector<int> permutation = {0, 1, 2};
    int prv = 2;
    do
    {
      if (prv == permutation[0]) continue;
      addBoxes(permutation);
      prv = permutation[0];
    }
    while (next_permutation(permutation.begin(), permutation.end()) && !ans);

    DEBUG
    {
      printf("\tpermutation: %d %d %d\n", permutation[0], permutation[1], permutation[2]);
      for (int i = 0; i < box.size(); ++i)
      {
        printf("\t");
        for (auto a : box[i])
          printf(" %d", a);
        printf("\n");
      }
    }

    sort(box.begin(), box.end(), greater<vector<int>>());

    seg = PersistentSegTree<SegNode>(values.size(), nil);
    seg.build();

    for (int i = box.size() - 1, j = 0; i >= 0 && !ans; --i, ++j)
    {
      int k = i;
      while (k - 1 >= 0 && box[i][0] == box[k - 1][0])
        --k;

      for (int e = k; e <= i; ++e)
      {
        if (box[e][1] > 0)
        {
          int res = seg.query(j, 0, box[e][1] - 1).value;
          DEBUG printf("\t%d | %d | %d\n", e, box[e][2], res);
          ans |= box[e][2] > res;
        }
        if (box[e][2] > 0)
        {
          int res = seg.query(j, 0, box[e][2] - 1).value;
          DEBUG printf("\t%d | %d | %d\n", e, box[e][1], res);
          ans |= box[e][1] > res;
        }
      }

      for (int e = k; e <= i; ++e, ++j)
        seg.update(j, box[e][1], SegNode{box[e][2]});

      i = k;
      --j;
    }

    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
