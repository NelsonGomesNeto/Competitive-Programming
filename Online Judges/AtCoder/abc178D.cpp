#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2000; int s;
const lli mod = 1e9 + 7;

lli memo[maxN];
lli solve(int sum = 0)
{
  if (sum > s) return false;
  if (sum == s) return true;
  if (memo[sum] != -1) return memo[sum];

  lli ans = 0;
  for (int i = 3; i <= s; i++)
    ans = (ans + solve(sum + i)) % mod;
  return memo[sum] = ans;
}

int main()
{
  while (scanf("%d", &s) != EOF)
  {
    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}