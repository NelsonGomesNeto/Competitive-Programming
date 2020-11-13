#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2, maxK = 1e5; int n, k;
const lli mod = 1e9 + 7;
int a[maxN];

lli memo[maxN + 1][maxK + 1], pmemo[maxN][maxK + 1];
lli solve(int i, int curr);
lli pref(int i, int curr)
{
  if (curr < 0) return 1;
  lli &ans = pmemo[i][curr];
  if (ans != -1) return ans;
  return ans = pref(i, curr - 1) + solve(i + 1, curr);
}
lli solve(int i = 0, int curr = k)
{
  if (i == n) return curr == 0;
  lli &ans = memo[i][curr];
  if (ans != -1) return ans;

  ans = 0;
  int end = min(a[i], curr);
  ans = (ans + pref(i, curr) - pref(i, curr - end - 1) + mod) % mod;

  return ans;
}

lli prefix[maxN][maxK + 2];
lli solve2()
{
  memset(memo, 0, sizeof(memo));
  memset(prefix, 0, sizeof(prefix));
  for (int x = 1; x <= k + 1; x++) prefix[0][x] = 1;

  for (int i = 0; i < n; i++)
    for (int x = 0; x <= k; x++)
    {
      // for (int j = 0, end = min(a[i], x); j <= end; j++)
      //   memo[i + 1][x] = (memo[i + 1][x] + memo[i][x - j]) % mod;
      // sum from x - min(a[i], x) to x

      int end = min(a[i], x);
      memo[i + 1][x] = (memo[i + 1][x]
                      + prefix[i][x + 1]
                      - prefix[i][x - end]
                      + mod) % mod;

      prefix[i + 1][x + 1] = (prefix[i + 1][x] + memo[i + 1][x]) % mod;
    }
  return memo[n][k];
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    // memset(memo, -1, sizeof(memo));
    // memset(pmemo, -1, sizeof(pmemo));
    // lli ans = solve();
    lli ans = solve2();
    printf("%lld\n", ans);
  }
  return 0;
}