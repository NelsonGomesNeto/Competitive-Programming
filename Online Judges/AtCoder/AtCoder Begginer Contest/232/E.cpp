#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli maxN = 1e9, maxK = 1e6; lli n, m; int k;
const lli mod = 998244353;
lli x1, Y1, x2, y2;

lli memo[maxK][2][2];
lli solve(int i = 0, bool sameRow = Y1 == y2, bool sameColumn = x1 == x2)
{
  if (i == k) return sameRow && sameColumn;
  lli &ans = memo[i][sameRow][sameColumn];
  if (ans != -1) return ans;

  ans = 0;
  ans = (ans + (n - 2 + sameColumn) * solve(i + 1, sameRow, false) % mod) % mod;
  ans = (ans + (m - 2 + sameRow) * solve(i + 1, false, sameColumn) % mod) % mod;
  if (!sameRow)
    ans = (ans + solve(i + 1, true, sameColumn)) % mod;
  if (!sameColumn)
    ans = (ans + solve(i + 1, sameRow, true)) % mod;

  return ans;
}

int main()
{
  while (~scanf("%lld %lld %d", &n, &m, &k))
  {
    scanf("%lld %lld %lld %lld", &x1, &Y1, &x2, &y2);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}