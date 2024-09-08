#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
const lli mod = 998244353;
char s[maxN + 1];
int c[maxN];

lli memo[maxN][11][1 << 10];
lli solve(int i = 0, int prv = 10, int mask = 0)
{
  if (i == n) return mask != 0;
  lli &ans = memo[i][prv][mask];
  if (ans != -1) return ans;

  ans = 0;
  if (c[i] == prv)
  {
    ans = (solve(i + 1, c[i], mask | (1 << c[i]))
         + solve(i + 1, prv, mask)) % mod;
  }
  else
  {
    ans = solve(i + 1, prv, mask);
    if (!(mask & (1 << c[i])))
      ans = (ans + solve(i + 1, c[i], mask | (1 << c[i]))) % mod;
  }
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", s);
    for (int i = 0; i < n; i++) c[i] = s[i] - 'A';

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}