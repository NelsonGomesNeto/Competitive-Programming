#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3 + 1; int n, s;
const lli mod = 998244353;
int a[maxN];

lli memo[maxN][maxN][2];
lli solve(int i = 0, int cs = 0, int t = 0)
{
  if (cs > s) return 0;
  if (i == n || t == 2) return cs == s;
  lli &ans = memo[i][cs][t];
  if (ans != -1) return ans;

  ans = 0;
  if (t == 0)
    ans = (ans + solve(i + 1) + solve(i, 0, 1)) % mod;
  else if (t == 1)
    ans = (ans + solve(i + 1, cs + a[i], 1) + solve(i + 1, cs, 1)
               + solve(i, cs, 2)) % mod;
  return ans;
}

int main()
{
  while (scanf("%d %d", &n, &s) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}