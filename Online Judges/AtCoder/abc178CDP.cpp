#include <stdio.h>
#include <string.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n;
const lli mod = 1e9 + 7;

lli memo[maxN][2][2];
lli solve(int i = 0, bool hasZero = false, bool hasNine = false)
{
  if (i == n) return hasZero && hasNine;
  if (memo[i][hasZero][hasNine] != -1) return memo[i][hasZero][hasNine];

  lli ans = 8LL * solve(i + 1, hasZero, hasNine) % mod;
  ans = (ans + solve(i + 1, true, hasNine)) % mod;
  ans = (ans + solve(i + 1, hasZero, true)) % mod;
  return memo[i][hasZero][hasNine] = ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}