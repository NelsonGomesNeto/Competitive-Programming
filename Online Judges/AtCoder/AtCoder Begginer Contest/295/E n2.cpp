#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353LL;

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

const int maxN = 2e3;
int n, m, k;
vector<int> a;
int zeros;

lli memo[maxN + 2][maxN + 2];
lli permutations(int x, int y)
{
  if (x < 0 || y < 0) return 0;
  // DEBUG printf("\t\t%d %d %d - %lld\n", x, y, z, memo[x][z]);
  if (x + y == 0) return 1;
  lli& ans = memo[x][y];
  if (ans != -1) return ans;
  ans = (permutations(x - 1, y) + permutations(x, y - 1)) % mod;
  return ans;
}

int main()
{
  memset(memo, -1, sizeof(memo));
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    // if (n == 10) return 0;
    const lli invM = inv(m);
    a.clear();
    a.resize(n);
    for (int& aa : a) scanf("%d", &aa);

    zeros = 0;
    for (const int aa : a) zeros += aa == 0;
    const lli invMpZeros = modPow(invM, zeros);

    const int required = n - k + 1;

    lli ans = 0;
    for (int x = 1; x <= m; ++x)
    {
      int atLeastX = 0;
      for (const int aa : a)
        atLeastX += aa != 0 && aa >= x;

      const int remaining = zeros - (required - atLeastX);
      DEBUG printf("%d | %d | %d %d\n", x, required, atLeastX, remaining);

      if (atLeastX >= required)
      {
        ans = (ans + 1) % mod;
        continue;
      }
      if (required - atLeastX > zeros) 
        continue;

      for (int below = 0; below <= remaining; ++below)
      {
        const int above = zeros - below;
        const lli p = permutations(below, above)
                    * modPow(m - x + 1, above) % mod
                    * modPow(x - 1, below) % mod
                    * invMpZeros % mod;
        DEBUG printf("\t%d | %d %d | %lld\n", x, below, above, p);
        ans = (ans + p) % mod;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
