#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

// C(n) = binomial(2n,n)/(n+1) = binomial(2n, n) - binomial(2n, n - 1)

const int maxX = 3e3;
lli mod;
lli c[maxX + 1];

lli catalan(lli n = maxX)
{
  if (n <= 1) return c[n] = 1;
  if (c[n] != -1) return c[n];
  c[n] = 0;
  for (int k = 0; k < n; k++)
    c[n] = (c[n] + catalan(k)*catalan(n - 1 - k) % mod) % mod;
  return c[n];
}

const int maxN = 2021; int r, n;
lli memo[maxN][maxN + 1];
lli solve(int i = 0, int chosen = 1)
{
  if (i == r - 1) return chosen >= 2 ? c[chosen - 1] * c[n - chosen] % mod : 0;
  lli &ans = memo[i][chosen];
  if (ans != -1) return ans;

  return ans = (solve(i + 1, chosen) + solve(i + 1, chosen + 1)) % mod;
}

int main()
{
  while (~scanf("%d %d %lld", &r, &n, &mod))
  {
    // mod = 1283412;
    memset(c, -1, sizeof(c));
    c[0] = c[1] = 1;
    catalan();

    DEBUG {
      for (int i = 0; i <= 6; i++)
        printf("\t%d - %lld\n", i, c[i]);
    }

    memset(memo, -1, sizeof(memo));
    DEBUG printf("\tinvalid: %lld\n", solve());
    lli ans = (c[n - 1] - solve() + 0 + mod) % mod;
    printf("%lld\n", ans);
  }

  return 0;
}