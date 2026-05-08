#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  DP ftw
  We can build up on O(n^2)' DP (Finding the optimal splitting point):
    dp[i] = max(dp(j) + beautyFromMinHeight[i : j], for j in [i + 1 : n - 1])

  Notice that we don't need to test for buildings after the closest smallest building:
    Suppose you will start a photo at building i, as soon as you include a smaller
    building j (h[j] < h[i]): from that point on the value you will get will be fully
    dependent on building j's answer.

    So we can reduce to:
      1: include closestSmaller[i] in i's photo
      2: don't include include closestSmaller[i] in i's photo
      dp[i] = max(
        dp(closestSmaller[i]) // 1
        max(dp(j) + beautyFromMinHeight[i : j], for j in [i + 1 : closestSmaller[i]]) // 2
      )

  Notice that we don't need to calculate beautyFromMinHeight[i : j], since we know which
  is the smallest building in that range:
    dp[i] = max(
      dp(closestSmaller[i]) // 1
      max(dp(j) + beauty[i], for j in [i + 1 : closestSmaller[i]]) // 2
    )

  We can also remove beauty[i] from that max, since it doesn't change with j:
    dp[i] = max(
      dp(closestSmaller[i]) // 1
      beauty[i] + max(dp(j), for j in [i + 1 : closestSmaller[i]]) // 2
    )

  Notice that I go TopDown from left to right. But what if we saved the answers from right to left?
  This way, we can use a SegmentTree to save the answers for each dp(i) and then query [i + 1 : closestSmallest[i]]
  in lg(n).

  O(n*lg(n)) done ^~^.
  Finding the closestSmaller can be done using SegmentTrees as well.

  You can optimize even further if you use stacks instead of SegmentTrees (for both DP and the closestSmaller).
  It's a bir harder, but you can look the idea in my code (I have a version using stacks as well).
*/

const lli inf = 1e16;
struct Data
{
  lli value;
  Data operator+(const Data &other)
  {
    return Data{max(value, other.value)};
  }
};
const Data nil = Data{-inf};

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

const int maxN = 3e5; int n;
const lli unused = 1e17;
int h[maxN];
lli b[maxN]; int closestSmaller[maxN];

lli memo[maxN];
lli solve(int i = 0)
{
  if (i == n)
    return 0;
  lli &ans = memo[i];
  if (ans != unused)
    return ans;

  ans = closestSmaller[i] == n ? b[i] : solve(closestSmaller[i]);
  ans = max(ans, segtree.query(i + 1, closestSmaller[i]).value + b[i]);
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &h[i]);
      h[i]--;
    }
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    // precalculate closestSmaller (could be done with segtree, but with stack is prettier and faster)
    stack<int> s;
    for (int i = n - 1; i >= 0; i--)
    {
      while (!s.empty() && h[i] < h[s.top()])
        s.pop();
      if (s.empty()) closestSmaller[i] = n;
      else closestSmaller[i] = s.top();
      s.push(i);
    }
    DEBUG
      for (int i = 0; i < n; i++)
        printf("%d (%d) - %d (%d)\n", i, h[i], closestSmaller[i], closestSmaller[i] == n ? -1 : h[closestSmaller[i]]);

    for (int i = 0; i < n; i++)
      memo[i] = unused;

    segtree = Segtree<Data>(n + 1, nil);
    for (int i = 0; i <= n; i++) segtree.data[i] = nil;
    segtree.build();
    for (int i = n - 1; i >= 0; i--)
    {
      DEBUG printf("\t%d (%d, %lld) - %lld || %lld\n", i, h[i], b[i], solve(i), segtree.query(i + 1, closestSmaller[i]).value);
      segtree.update(i, Data{solve(i)});
    }
    printf("%lld\n", solve());

    if (n == 5)
      return 0;
  }
  return 0;
}