#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n; lli p;

int memoSzDelta[maxN + 1];
lli memo[maxN + 1][2*maxN + 1], pref[2*maxN + 1][maxN + 1];
vector<vector<int>> szsToDelta;

lli solve(int i, int totalSize);
lli prefSolve(int totalSize, int i)
{
  if (i > n) return false;
  if (i == n) return totalSize < n;
  lli &ans = pref[totalSize][i];
  if (ans != -1) return ans;
  return ans = (solve(i, totalSize) + prefSolve(totalSize, i + 1)) % p;
}
lli solve(int i = 0, int totalSize = 0)
{
  lli &ans = memo[i][totalSize];
  if (ans != -1) return ans;

  lli ways = 25 + (i == 0);
  ans = 0;
  for (int delta = 2; delta < szsToDelta.size(); ++delta)
  {
    if (totalSize + delta > 2*n) continue;
    int minSz = szsToDelta[delta][0], maxSz = szsToDelta[delta].back();
    if (i + minSz > n) continue;

    lli hehe = prefSolve(totalSize + delta, i + minSz);
    if (i + maxSz + 1 <= n)
      hehe = (hehe - prefSolve(totalSize + delta, i + maxSz + 1) + p) % p;

    lli toAdd = ways * hehe;
    ans = (ans + toAdd % p) % p;
  }

  return ans;
}

lli solve2()
{
  memset(memo, 0, sizeof(memo));
  memset(pref, 0, sizeof(pref));
  for (int totalSize = 0; totalSize <= 2*n; ++totalSize)
    pref[totalSize][n] = totalSize < n;

  for (int totalSize = 2*n; totalSize >= 0; --totalSize)
  {
    for (int i = n - 1; i >= 0; --i)
    {
      lli ways = 25 + (i == 0);
      // lli &ans = memo[i][totalSize];
      // for (int delta = 2; delta < szsToDelta.size(); ++delta)
      //   if (totalSize + delta <= 2*n)
      //     for (int sz : szsToDelta[delta])
      //       if (i + sz <= n)
      //         ans = (ans + ways * memo[i + sz][totalSize + delta] % p) % p;

      // for (int sz = 1, end = n - i; sz <= end; ++sz)
      //   memo[i][totalSize] = (memo[i][totalSize] + ways * memo[i + sz][totalSize + memoSzDelta[sz]] % p) % p;

      pref[totalSize][i] = pref[totalSize][i + 1];
      for (int delta = 2; delta < szsToDelta.size(); ++delta)
      {
        if (totalSize + delta > 2*n) continue;
        int minSz = szsToDelta[delta][0], maxSz = szsToDelta[delta].back();
        if (i + minSz > n) continue;

        lli hehe = pref[totalSize + delta][i + minSz];
        if (i + maxSz + 1 <= n)
          hehe = (hehe - pref[totalSize + delta][i + maxSz + 1] + p) % p;

        lli toAdd = ways * hehe % p;
        memo[i][totalSize] = (memo[i][totalSize] + toAdd) % p;
        pref[totalSize][i] = (pref[totalSize][i] + toAdd) % p;
      }
    }
  }

  return memo[0][0];
}

int main()
{
  for (int i = 1; i <= maxN; ++i)
  {
    memoSzDelta[i] = 1 + to_string(i).size();
    while (szsToDelta.size() <= memoSzDelta[i]) szsToDelta.push_back(vector<int>());
    szsToDelta[memoSzDelta[i]].push_back(i);
  }

  while (~scanf("%d %lld", &n, &p))
  {
    memset(memo, -1, sizeof(memo));
    memset(pref, -1, sizeof(pref));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
