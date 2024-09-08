#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  unordered_map<int> values;
  Data operator+(const Data &other)
  {
    Data ans = Data{};
    ans.values.resize(values.size() + other.values.size());
    merge(values.begin(), values.end(), other.values.begin(), other.values.end(), ans.values.begin());
    return ans;
  }
  void put(Data &other)
  {
    for (int i: other.values)
      values.push_back(i);
  }
};
Data nil = Data{{}};

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
  T query(lli yMin, int qlo, int qhi)
  {
    T ans;
    query(ans, yMin, qlo, qhi, 1, 0, size - 1);
    sort(ans.values.begin(), ans.values.end()); // optional
    return ans;
  }
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
  void query(T &ans, lli yMin, int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return;
    if (lo >= qlo && hi <= qhi) return ans.put(st[i]);
    int mid = (lo + hi) >> 1;
    query(ans, yMin, qlo, qhi, 2*i, lo, mid);
    query(ans, yMin, qlo, qhi, 2*i + 1, mid + 1, hi);
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

const int maxN = 1e6; int n, q;
vector<int> a;

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d", &n);
    a.clear();
    for (int i = 0; i < n; ++i)
    {
      a.push_back(0);
      scanf("%d", &a.back());
    }

    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; ++i)
      segtree.data[i] = Data{a[i], a[i]};
    segtree.build();

    scanf("%d", &q);
    int ans = 0;
    for (int qq = 1; qq <= q; ++qq)
    {
      int l, r; scanf("%d %d", &l, &r); --l, --r;
      if (r - l + 1 <= 2)
      {
        ans += (r - l + 1) & 1;
        continue;
      }

      bool can = false;
      bool shouldSwap = false;
      for (int mid : {(l + r - 2) >> 1, (l + r) >> 1})
      {
        DEBUG printf("\t\t%d\n", mid);
        int onesDelta = 0;
        for (int j = 0; j < 26 && onesDelta <= 1; ++j)
        {
          Data leftCount = segtree.query(l, mid);
          Data rightCount = segtree.query(mid + 1, r);
          
          // int leftCount = acc[j][mid + 1] - acc[j][l];
          // int rightCount = acc[j][r + 1] - acc[j][mid + 1];
          // if (shouldSwap) swap(leftCount, rightCount);
          // int delta = rightCount - leftCount;

          // if (delta == 1)
          //   ++onesDelta;
          // else if (delta > 1 || delta < 0)
          //   onesDelta = 2;

          // DEBUG {
          //   if (leftCount || rightCount)
          //     printf("\t\t%d %c - %d %d\n", mid, 'a' + j, leftCount, rightCount);
          // }
        }
        can |= onesDelta == 1;
        shouldSwap = true;
      }
      DEBUG printf("\t%d %d - %d | %s\n", l, r, can, string(ss).substr(l, r - l + 1).c_str());
      ans += can;
    }

    printf("Case #%d: %d\n", testCase, ans);
  }
  return 0;
}
