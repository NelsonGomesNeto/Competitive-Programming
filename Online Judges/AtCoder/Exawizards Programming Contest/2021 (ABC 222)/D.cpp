#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;

const int maxN = 3e3; int n;
int a[maxN], b[maxN];

lli memo[maxN][maxN + 1], pmemo[maxN][maxN + 1];
lli solve(int i, int prv);
lli pref(int i, int j)
{
  if (j == -1) return 0;
  lli &ans = pmemo[i][j];
  if (ans != -1) return ans;
  return ans = (pref(i, j - 1) + solve(i + 1, j)) % mod;
}
lli solve(int i = 0, int prv = 0)
{
  if (i == n) return 1;
  lli &ans = memo[i][prv];
  if (ans != -1) return ans;

  ans = 0;
  if (prv <= b[i])
    ans = (pref(i, b[i]) - pref(i, max(prv, a[i]) - 1) + mod) % mod;
  // for (int j = max(prv, a[i]); j <= b[i]; j++)
  //   ans = (ans + solve(i + 1, j)) % mod;

  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);

    memset(memo, -1, sizeof(memo));
    memset(pmemo, -1, sizeof(pmemo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
