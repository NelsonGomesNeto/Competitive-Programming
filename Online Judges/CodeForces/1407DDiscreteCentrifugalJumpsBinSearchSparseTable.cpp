#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  For each skyscraper i: it might go to 3 others
    1: above jump to j (max(h[i], h[j]) < min(h[i + 1 : j - 1]))
      if h[i] >= h[j]
        you need to find the first skyscraper <= h[i]
      if h[i] < h[j]:
        same as above, but from j to i
    2: below jump to j (min(h[i], h[j]) > max(h[i + 1 : j - 1]))
      very similar to above
    3: jump to i + 1
      very basic, nothing to do here

  After calculation the next for each i: use DP to find the choice of jumps
*/

const int maxN = 3e5, maxLog = 20; int n;
const lli inf = 1e9 + 1;
lli h[maxN];
pair<lli, int> lowLeft[maxN], lowRight[maxN];
pair<lli, int> highLeft[maxN], highRight[maxN];

int logdp[maxN + 1];
struct MaxData
{
  lli maximum;
  MaxData operator+(const MaxData &other)
  {
    return MaxData{max(maximum, other.maximum)};
  }
};
const MaxData maxNil = MaxData{0};
struct MinData
{
  lli minimum;
  MinData operator+(const MinData &other)
  {
    return MinData{min(minimum, other.minimum)};
  }
};
const MinData minNil = MinData{inf};

template<class T>
struct SparseTable
{
  int size, logn;
  T nil;
  vector<T> data;
  vector<vector<T>> st;
  SparseTable() { }
  SparseTable(int size, T nil) : size(size), nil(nil)
  {
    logn = floor(log2(size)) + 1;
    data.resize(size);
    st.resize(size, vector<T>(logn + 1));
  }
  void build()
  {
    for (int i = 0; i < size; i++)
      st[i][0] = data[i];
    for (int j = 1; j <= logn; j++)
      for (int i = 0, shift = (1 << (j - 1)); i + shift < size; i++)
        st[i][j] = st[i][j - 1] + st[i + shift][j - 1];
  }
  T query(int lo, int hi)
  {
    int qs = logdp[hi - lo + 1];
    return st[lo][qs] + st[hi - (1 << qs) + 1][qs];
    // T ans = nil;
    // for (int j = logn; j >= 0; j --)
    //   if (lo + (1 << j) - 1 <= hi)
    //   {
    //     ans = ans + st[lo][j];
    //     lo += (1 << j);
    //   }
    // return ans;
  }
};
SparseTable<MinData> minSparseTable;
SparseTable<MaxData> maxSparseTable;

bool can(int lo, int hi)
{
  if (lo + 1 == hi) return true;
  lli minimum = minSparseTable.query(lo + 1, hi - 1).minimum, maximum = maxSparseTable.query(lo + 1, hi - 1).maximum;
  return minimum > max(h[lo], h[hi]) || maximum < min(h[lo], h[hi]);
}

list<int> nxtOver[maxN], nxtBelow[maxN];
int memo[maxN];
int solve(int i = 0)
{
  if (i >= n - 1) return 0;
  if (memo[i] != -1) return memo[i];

  int ans = 1e6;
  for (int j: nxtOver[i])
    ans = min(ans, solve(j) + 1);
  for (int j: nxtBelow[i])
    ans = min(ans, solve(j) + 1);
  ans = min(ans, solve(i + 1) + 1);
  return memo[i] = ans;
}

int lower(int lo, int hi, int idx, bool upperBound)
{
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (minSparseTable.query(mid, idx - 1).minimum <= h[idx]) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (minSparseTable.query(idx + 1, mid).minimum <= h[idx]) hi = mid;
      else lo = mid + 1;
    }
  }
  if (upperBound)
    return minSparseTable.query(lo, idx - 1).minimum <= h[idx] ? lo : -1;
  return minSparseTable.query(idx + 1, lo).minimum <= h[idx] ? lo : -1;
}
int higher(int lo, int hi, int idx, bool upperBound)
{
  while (lo < hi)
  {
    int mid = (lo + hi + upperBound) >> 1;
    if (upperBound)
    {
      if (maxSparseTable.query(mid, idx - 1).maximum >= h[idx]) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (maxSparseTable.query(idx + 1, mid).maximum >= h[idx]) hi = mid;
      else lo = mid + 1;
    }
  }
  if (upperBound)
    return maxSparseTable.query(lo, idx - 1).maximum >= h[idx] ? lo : -1;
  return maxSparseTable.query(idx + 1, lo).maximum >= h[idx] ? lo : -1;
}

int main()
{
  logdp[1] = 0;
  for (int i = 2; i <= maxN; i ++) logdp[i] = logdp[i >> 1] + 1;

  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &h[i]);
      nxtOver[i].clear(), nxtBelow[i].clear();
    }

    minSparseTable = SparseTable<MinData>(n, minNil);
    maxSparseTable = SparseTable<MaxData>(n, maxNil);
    for (int i = 0; i < n; i++)
      minSparseTable.data[i].minimum = maxSparseTable.data[i].maximum = h[i];
    minSparseTable.build(), maxSparseTable.build();

    for (int i = 0; i < n; i++)
    {
      int prv = i ? lower(0, i - 1, i, true) : -1;
      int nxt = i + 1 < n ? lower(i + 1, n - 1, i, false) : -1;
      if (prv != -1)
        nxtOver[prv].push_back(i);
      if (nxt != -1)
        nxtOver[i].push_back(nxt);
    }

    for (int i = 0; i < n; i++)
    {
      int prv = i ? higher(0, i - 1, i, true) : -1;
      int nxt = i + 1 < n ? higher(i + 1, n - 1, i, false) : -1;
      if (prv != -1)
        nxtBelow[prv].push_back(i);
      if (nxt != -1)
        nxtBelow[i].push_back(nxt);
    }

    DEBUG {
      for (int i = 0; i < n; i++)
        printf("%3d%c", i, i < n - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i++)
        printf("%3lld%c", h[i], i < n - 1 ? ' ' : '\n');
      for (int i = 0; i < n; i++)
        if (!nxtOver[i].empty())
        {
          printf("%d -", i);
          for (int j: nxtOver[i])
            printf(" %d", j);
          printf("\n");
        }
      for (int i = 0; i < n; i++)
        if (!nxtBelow[i].empty())
        {
          printf("%d -", i);
          for (int j: nxtBelow[i])
            printf(" %d", j);
          printf("\n");
        }
    }

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}