#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n, k, q;
const lli mod = 1e9 + 7;
lli a[maxN];

lli memo[maxN + 1][maxN];
lli cnt[maxN];
// cnt[i] == paths with length "k" that end in "i" (or start)
lli solve(int sz, int i)
{
  lli &ans = memo[sz][i];
  if (sz == 0) return ans = 1;
  if (ans != -1) return ans;

  ans = 0;
  if (i) ans = (ans + solve(sz - 1, i - 1)) % mod;
  if (i + 1 < n) ans = (ans + solve(sz - 1, i + 1)) % mod;
  return ans;
}

int main()
{
  int tt = 0;
  while (~scanf("%d %d %d", &n, &k, &q))
  {
    if (tt++) printf("-----------------\n");

    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; i++)
      solve(k, i);
    for (int i = 0; i < n; i++)
    {
      cnt[i] = 0;
      for (int j = 0; j <= k; j++)
        cnt[i] = (cnt[i] + memo[j][i] * memo[k - j][i] % mod) % mod;
    }

    lli ans = 0;
    for (int i = 0; i < n; i++)
      ans = (ans + cnt[i] * a[i] % mod) % mod;

    for (int qq = 1; qq <= q; qq++)
    {
      int p; lli x; scanf("%d %lld", &p, &x); p--;
      ans = (ans + cnt[p] * ((x - a[p] + mod) % mod) % mod + mod) % mod;
      a[p] = x;
      printf("%lld\n", ans);
    }
    DEBUG {
      for (int i = 0; i < n; i++)
        printf("\t%d %lld\n", i, cnt[i]);
    }
  }
  return 0;
}
