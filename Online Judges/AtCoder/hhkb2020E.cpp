#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, m, k;
const lli mod = 1e9 + 7;
char mat[maxN][maxN + 1];
int horizontal[maxN][maxN], vertical[maxN][maxN];

bool valid(int i, int j)
{
  return i >= 0 && j >= 0 && i < n && j < m && mat[i][j] == '.';
}

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1) ans = ans * x % mod;
    x = x * x % mod, y >>= 1;
  }
  return(ans);
}

lli calc(int i, int j)
{
  lli total = horizontal[i][j] + vertical[i][j] + 1;
  lli remain = k - total;
  return (modPow(2, total) - 1 + mod) * modPow(2, remain) % mod;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    memset(horizontal, 0, sizeof(horizontal));
    memset(vertical, 0, sizeof(vertical));

    k = 0;
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", mat[i]);
      for (int j = 0; j < m; j++)
        k += mat[i][j] == '.';
    }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (mat[i][j] == '.')
        {
          int delta = 1, h = 0;
          while (true)
          {
            int ni = i, nj = j + delta;
            if (!valid(ni, nj)) break;
            h++, delta++;
          }

          delta = 0;
          while (true)
          {
            int ni = i, nj = j + delta;
            if (!valid(ni, nj)) break;
            horizontal[ni][nj] += h, delta++;
          }

          j += delta - 1;
        }

    for (int j = 0; j < m; j++)
      for (int i = 0; i < n; i++)
        if (mat[i][j] == '.')
        {
          int delta = 1, v = 0;
          while (true)
          {
            int ni = i + delta, nj = j;
            if (!valid(ni, nj)) break;
            v++, delta++;
          }

          delta = 0;
          while (true)
          {
            int ni = i + delta, nj = j;
            if (!valid(ni, nj)) break;
            vertical[ni][nj] += v, delta++;
          }

          i += delta - 1;
        }

    DEBUG
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          printf("%3d%c", horizontal[i][j] + vertical[i][j] + (mat[i][j] == '.'), j < m - 1 ? ' ' : '\n');

    lli ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (mat[i][j] == '.')
          ans = (ans + calc(i, j)) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}