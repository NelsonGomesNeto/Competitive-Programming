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

  int build(int lo, int hi)
  {
    if (lo == hi)
    {
      st.push_back(data[lo]);
      return st.size() - 1;
    }
    int mid = (lo + hi) >> 1, newRootIdx = st.size();
    st.push_back(nil);
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

const int maxN = 1e5, maxS = 1e6; int n;
char s[maxS + 2];
int dayVersion[maxN + 1];
int d[maxN];
int x[maxN + 1];

void readline()
{
  s[0] = '\0';
  char c; int i = 0;
  for (i = 0; scanf("%c", &c) && c != '\n'; i++)
    s[i] = c;
  s[i] = '\n';
  s[i + 1] = '\0';
}

// vector<string> split (const string &s, char delim) {
//   vector<string> result;
//   stringstream ss (s);
//   string item;

//   while (getline(ss, item, delim)) {
//     result.push_back(item);
//   }

//   return result;
// }

int main()
{
  while (~scanf("%d", &n))
  {
    // version 0 -> day 0
    // version 1 -> day 1
    // version 2 -> day 1
    // version 3 -> day 2
    // version 4 -> day 2
    // version 2*n -> day n
    segtree = PersistentSegTree<SegNode>(n, nil);
    for (int i = 0; i < n; i++)
      segtree.data[i] = nil;
    segtree.build();

    getchar();
    dayVersion[0] = 0; int versions = 0;
    for (int i = 0; i < n; i++)
    {
      readline();

      int j = 0, before = 0;
      while (s[j] != '\n' && s[j])
      {
        while (s[j] != ' ' && s[j] != '\n')
          j++;

        char op; int u; sscanf(s + before, "%c%d", &op, &u);
        DEBUG printf("\t%d [%s] - %c%d\n", i, s + before, op, u);
        segtree.update(versions++, u, SegNode(op == '+' ? 1 : 0));

        before = ++j;
      }
      dayVersion[i + 1] = versions;
    }

    for (int i = 0; i < n; i++)
      scanf("%d", &d[i]);

    x[0] = 0;
    for (int i = 0; i < n; i++)
    {
      x[i + 1] = (x[i] + segtree.query(dayVersion[d[i]], x[i], n - 1).value) % n;
      DEBUG printf("\t\t%d - %d - %d %d\n", i + 1, x[i + 1], d[i], dayVersion[d[i]]);
    }
    printf("%d\n", x[n]);
  }
  return 0;
}