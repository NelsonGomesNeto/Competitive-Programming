#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct DSU
{
  int size;
  vector<int> parents;
  DSU() { parents.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init() { parents.resize(size, -1); }
  int root(int u) { return parents[u] < 0 ? u : parents[u] = root(parents[u]); }
  void merge(int u, int v)
  {
    u = root(u), v = root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int setSize(int u) { return -parents[root(u)]; }
  bool sameSet(int u, int v) { return root(u) == root(v); }
};
DSU dsu;

const int maxX = 1e5 + 1;
lli mod = 1e9 + 7; // could be two as well

lli fat[maxX], invFat[maxX];
lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}
lli choose(lli nn, lli kk)
{
  if (nn < kk) return 0;
  if (nn < mod) return fat[nn] * invFat[kk] % mod * invFat[nn - kk] % mod;
  lli ans = 1;
  while (nn || kk)
  {
    lli nnn = nn % mod, kkk = kk % mod;
    nn /= mod, kk /= mod;
    ans = ans * choose(nnn, kkk) % mod;
  }
  return ans;
}
// nn = stars, kk = bars
lli starsAndBars(lli nn, lli kk)
{
  return choose(nn + kk, kk);
}

const int maxN = 3e3; int n; lli p;
int edges;

DSU addEdge(int i, DSU curr)
{
  int u, v;
  if (i <= n - 2) u = i, v = i + 1; // 0 - (n - 1)
  else if (i <= 2*n - 3) u = i + 1, v = i + 2; // (n) - n + (n - 1)
  else u = i - 2*(n - 1), v = i - n + 2;
  curr.merge(u, v);
  return curr;
}

int pendingRemoval;
int solve(int i = 0, int removed = 0, DSU curr = DSU(2*n), string now = "")
{
  if (i == edges)
  {
    if (removed != pendingRemoval) return false;
    if (curr.setSize(0) == 2*n)
    {
      return true;
    }
    // printf("%s\n", now.c_str());
    return false;
  }
  if (edges - i < pendingRemoval - removed) return false;

  if (removed < pendingRemoval) return solve(i + 1, removed + 1, curr, now + "0") + solve(i + 1, removed, addEdge(i, curr), now + "1");
  else return solve(i + 1, removed, addEdge(i, curr), now + "1");
}

struct HistoryQueue
{
  int history;
  HistoryQueue add(bool now)
  {
    return HistoryQueue{((history << 1) | now) & 0b111};
  }
  bool operator[](int idx)
  {
    return (history >> (idx - 1)) & 1;
  }
};
HistoryQueue nilHistory = {0};

// border, top, bottom, border, ..., border, top, bottom, border = 3*n - 2
inline bool isTop(int i) { return i % 3 == 1; }
inline bool isBottom(int i) { return i % 3 == 2; }
inline bool isBorder(int i) { return i % 3 == 0; }
int invalids;
lli memo[maxN][3*maxN - 2][8];
lli countInvalids(int toRemove, int i = 0,
                  HistoryQueue hq = nilHistory, bool madeInvalid = false)
{
  if (toRemove == 0) return madeInvalid;
  if (madeInvalid) return choose(edges - i, toRemove);
  if (i == edges) return 0;

  lli &ans = memo[toRemove][i][hq.history];
  // if (ans != -1) return ans;

  ans = countInvalids(toRemove, i + 1, hq.add(false), false);

  bool hasMatch = false;
  if (hq[2] && (i == 2 || i == edges - 1))
    hasMatch = true;
  if (hq[1] && (i == 1 || i == edges - 1 || isBottom(i)))
    hasMatch = true;
  if (hq[2] && hq[3] && isBottom(i))
    hasMatch = true;
  if (hq[1] && hq[3] && isTop(i))
    hasMatch = true;

  if (toRemove)
    ans = (ans + countInvalids(toRemove - 1, i + 1, hq.add(true), hasMatch)) % p;

  return ans;
}

int main()
{
  int tests = 0;
  while (~scanf("%d %lld", &n, &p))
  {
    if (tests++) printf("---------------\n");

    mod = p;
    fat[0] = 1;
    for (lli i = 1; i < maxX; i++)
      fat[i] = i * fat[i - 1] % mod;
    for (int i = 0; i < maxX; i++)
      invFat[i] = inv(fat[i]);

    edges = 3*n - 2;

    // pendingRemoval = 3;
    // lli hehe = solve();
    // printf("\t%lld\n", hehe);

    memset(memo, -1, sizeof(memo));
    for (int i = 1; i < n; ++i)
    {
      lli ans = 3*n - 2;
      if (i > 1)
      {
        lli invalidWays = countInvalids(i);
        lli allWays = choose(edges, i);
        ans = (allWays - invalidWays + p) % p;
        // printf("\t%d - %lld %lld\n", i, allWays, invalidWays);
      }
      pendingRemoval = i;
      printf("%d%c", solve(), i + 1 < n ? ' ' : '\n');
    }
  }
  return 0;
}