#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, m, k;
const lli mod = 1e9 + 7;

lli memo[maxN][maxN + 1], pmemo[maxN][maxN + 1];
lli solve(int i, int left);
lli pref(int i, int left)
{
  if (left < 0) return 0;
  lli &ans = pmemo[i][left];
  if (ans != -1) return ans;
  return ans = (pref(i, left - 1) + solve(i + 1, left)) % mod;
}
lli solve(int i = 0, int left = n)
{
  if (left < 0) return 0;
  if (i == m) return left == 0;
  lli &ans = memo[i][left];
  if (ans != -1) return ans;

  ans = (pref(i, left - 1) - pref(i, left - min(left, k) - 1) + mod) % mod;
  // for (int j = min(left, k); j >= 1; j--)
  //   ans = (ans + solve(i + 1, left - j)) % mod;
  return ans;
}
lli solve2()
{
  memset(memo, 0, sizeof(memo));
  memset(pmemo, 0, sizeof(pmemo));
  for (int i = 1; i <= k; i++)
    memo[m - 1][i] = 1;
  for (int i = 1; i <= n; i++)
    pmemo[m - 1][i] = (pmemo[m - 1][i - 1] + memo[m - 1][i]) % mod;

  for (int i = m - 2; i >= 0; i--)
    for (int left = 1; left <= n; left++)
    {
      // for (int p = min(left, k); p >= 1; p--)
      //   memo[i][left] = (memo[i][left] + memo[i + 1][left - p]) % mod;
      // left - min(left, k) to left - 1
      memo[i][left] = (pmemo[i + 1][left - 1] - pmemo[i + 1][left - min(left, k) - 1] + mod) % mod;
      pmemo[i][left] = (pmemo[i][left - 1] + memo[i][left]) % mod;
    }

  return memo[0][n];
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    memset(memo, -1, sizeof(memo));
    memset(pmemo, -1, sizeof(pmemo));
    lli ans = solve2();
    printf("%lld\n", ans);
  }
  return 0;
}
