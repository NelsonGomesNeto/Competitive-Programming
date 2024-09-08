#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxK = 10; int n, k;
pair<int, int> lr[maxK];

vector<int> s[maxK];
const lli mod = 998244353;
lli memo[maxN];

int lowerBound(int j, int target)
{
  int lo = 0, hi = s[j].size() - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (s[j][mid] <= target) lo = mid;
    else hi = mid - 1;
  }
  return s[j][lo] <= target ? lo : -1;
}

struct Data
{
  lli value;
  Data operator+(const Data &other)
  {
    return Data{(value + other.value) % mod};
  }
};
const Data nil = Data{0LL};

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
      st[i] = (st[i] + value);
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
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < k; i++)
    {
      s[i].clear();
      scanf("%d %d", &lr[i].first, &lr[i].second);
      for (int j = 0, end = lr[i].second - lr[i].first + 1; j < end; j++)
        s[i].push_back(lr[i].first + j);
    }
    segtree = Segtree<Data>(n + 1, nil);
    for (int i = 0; i <= n; i++)
      segtree.data[i].value = 0;
    segtree.build();

    // memset(memo, 0, sizeof(memo));
    // memo[0] = 1;
    segtree.update(0, Data{1LL});
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < k; j++)
      {
        int last = lowerBound(j, i);
        if (last >= 0)
        {
          Data got = segtree.query(i - s[j][last], i - s[j][0]);
          // for (int jj = 0; jj <= last; jj++)
          //   segtree.update(i, segtree.query(i - s[j][jj], i - s[j][jj]));
            // memo[i] = (memo[i] + memo[i - s[j]]) % mod;
          segtree.update(i, got);
        }
      }

    lli ans = segtree.query(n - 1, n - 1).value;
    printf("%lld\n", ans);
  }
  return 0;
}