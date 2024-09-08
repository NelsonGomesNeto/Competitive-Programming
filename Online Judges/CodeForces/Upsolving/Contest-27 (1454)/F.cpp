#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];
vector<int> nums;
vector<int> leftPos[maxN], rightPos[maxN];

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{min(value, other.value)};
  }
};
const Data nil = Data{(int)1e9};

// DON'T FORGET TO DEFINE THE NIL!!!
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
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
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
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
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
Segtree<Data> segtree;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    nums.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      nums.push_back(a[i]);
    }
    sort(nums.begin(), nums.end());
    nums.resize(distance(nums.begin(), unique(nums.begin(), nums.end())));

    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
    {
      a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
      segtree.data[i] = Data{a[i]};
    }
    segtree.build();

    for (int i = 0; i < nums.size(); i++)
      leftPos[i].clear(), rightPos[i].clear();

    int mx = 0;
    for (int i = 0; i < n; i++)
    {
      mx = max(mx, a[i]);
      leftPos[mx].push_back(i);
    }
    mx = 0;
    for (int i = n - 1; i >= 0; i--)
    {
      mx = max(mx, a[i]);
      rightPos[mx].push_back(i);
    }
    for (int i = 0; i < nums.size(); i++)
      sort(rightPos[i].begin(), rightPos[i].end());

    int l = -1, r = -1;
    for (int i = 0; i < nums.size(); i++)
    {
      vector<int> realPos;
      for (int j = 0; j < leftPos[i].size(); j++)
      {
        int k = j;
        while (k + 1 < leftPos[i].size() && leftPos[i][k + 1] == leftPos[i][k + 1] + 1) k++;
        realPos.push_back(leftPos[i][j]);
        j = k;
      }
      leftPos[i] = realPos;
    }
    for (int i = 0; i < nums.size(); i++)
    {
      vector<int> realPos;
      for (int j = 0; j < rightPos[i].size(); j++)
      {
        int k = j;
        while (k + 1 < rightPos[i].size() && rightPos[i][k + 1] == rightPos[i][k + 1] + 1) k++;
        realPos.push_back(rightPos[i][j]);
        j = k;
      }
      rightPos[i] = realPos;
    }

    for (int i = 0; i < nums.size() && l == -1; i++)
    {
      for (int j = 0; j < leftPos[i].size() && l == -1; j++)
        for (int k = lower_bound(rightPos[i].begin(), rightPos[i].end(), leftPos[i][j] + 2) - rightPos[i].begin(); k < rightPos[i].size(); k++)
        {
          int ll = leftPos[i][j], rr = rightPos[i][k];
          if (ll + 1 > rr - 1) continue;
          int value = segtree.query(ll + 1, rr - 1).value;
          if (value == i)
            l = ll, r = rr;
          if (value < i)
            break;
        }
    }

    if (l == -1) printf("NO\n");
    else
    {
      int x = l + 1, y = r - l - 1;
      int z = n - (x + y);
      printf("YES\n%d %d %d\n", x, y, z);
    }
  }
  return 0;
}
