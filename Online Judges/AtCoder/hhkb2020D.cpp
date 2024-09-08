#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, m, k;
const lli mod = 1e9 + 7;
char mat[maxN][maxN + 1];
int willLight[maxN][maxN];

int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
bool valid(int i, int j)
{
  return i >= 0 && j >= 0 && i < n && j < m && mat[i][j] == '.';
}
void fill(int i, int j)
{
  int total = 1;
  for (int d = 0; d < 4; d++)
  {
    int delta = 1;
    while (true)
    {
      int ni = i + di[d]*delta, nj = j + dj[d]*delta;
      if (!valid(ni, nj)) break;
      total++;
    }
  }

  willLight[i][j] = total;
  for (int d = 0; d < 4; d++)
  {
    int delta = 1;
    while (true)
    {
      int ni = i + di[d]*delta, nj = j + dj[d]*delta;
      if (!valid(ni, nj)) break;
      willLight[ni][nj] = total;
    }
  }
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
  lli remain = k - willLight[i][j];
  return willLight[i][j] * modPow(2, remain) % mod;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        willLight[i][j] = -1;

    k = 0;
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", mat[i]);
      for (int j = 0; j < m; j++)
        k += mat[i][j] == '.';
    }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (mat[i][j] == '.' && willLight[i][j] == -1)
          fill(i, j);

    lli ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (mat[i][j] == '.')
          ans = (ans + calc(i, j)) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}