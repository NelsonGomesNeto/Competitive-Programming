#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n, m, k;
char mat[maxN][maxN + 1];

const lli mod = 998244353;

lli memo[maxN][maxN];
lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}
lli pot[maxN*maxN + 1];
lli inv3;
lli solve2(int i = 0, int j = 0, int unknown = 0)
{
  if (i >= n || j >= m) return 0;
  if (i == n - 1 && j == m - 1) return pot[(n*m - k) - 0];
  lli &ans = memo[i][j];
  if (ans != -1) return ans;
  
  ans = 0;
  if (mat[i][j] == 'R')
    ans = solve2(i, j + 1, unknown);
  else if (mat[i][j] == 'D')
    ans = solve2(i + 1, j, unknown);
  else if (mat[i][j] == 'X')
  {
    ans = (solve2(i, j + 1, unknown) + solve2(i + 1, j, unknown)) % mod;
  }
  else
  {
    lli a = 2LL * solve2(i, j + 1, unknown + 1) % mod;
    lli b = 2LL * solve2(i + 1, j, unknown + 1) % mod;
    ans = (a + b) * inv3 % mod;
  }
  return ans;
}

int main()
{
  inv3 = inv(3);
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    pot[0] = 1;
    for (int i = 1; i <= n*m; i++)
      pot[i] = 3LL * pot[i - 1] % mod;

    memset(mat, '.', sizeof(mat));
    for (int i = 0; i < n; i++)
      mat[i][n] = '\0';
    for (int kk = 0; kk < k; kk++)
    {
      int i, j; char c; scanf("%d %d %c", &i, &j, &c); i--, j--;
      mat[i][j] = c;
    }

    DEBUG
      for (int i = 0; i < n; i++)
        printf("\t%s\n", mat[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve2();
    printf("%lld\n", ans);
  }
  return 0;
}