#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const lli mod = 1e9 + 7;
lli c[maxN];

lli memo[maxN];
lli solve(int i = 0)
{
  if (i == n) return 1;
  lli &ans = memo[i];
  if (ans != -1) return ans;

  ans = max(0LL, (c[i] - i)) * solve(i + 1) % mod;
  // ans = (ans - solve(i + 1) * i % mod + mod) % mod;
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &c[i]);
    sort(c, c+n);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}