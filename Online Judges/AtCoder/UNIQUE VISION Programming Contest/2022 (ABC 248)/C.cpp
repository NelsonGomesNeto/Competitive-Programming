#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, m, k;
const int maxSum = maxN * maxN;
const lli mod = 998244353;

lli memo[maxN][maxSum + 1];
lli solve(int i = 0, int sum = 0)
{
  if (sum > k) return false;
  if (i == n) return true;
  lli &ans = memo[i][sum];
  if (ans != -1) return ans;
  ans = 0;
  for (int a = 1; a <= m; ++a)
    ans = (ans + solve(i + 1, sum + a)) % mod;
  return ans;
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}