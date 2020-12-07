#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
const lli mod = 1e9 + 7;
int mat[maxN][maxN];

lli modExp(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = (ans * x) % mod;
    x = (x * x) % mod, y >>= 1LL;
  }
  return ans;
}

int main()
{
  scanf("%d %d", &n, &m);
  memset(mat, -1, sizeof(mat));
  for (int i = 0; i < n; i ++)
  {
    int r; scanf("%d", &r);
    for (int j = 0; j < r; j ++)
      mat[i][j] = 1;
    if (r < m) mat[i][r] = 0;
  }
  bool valid = true;
  for (int j = 0; j < m; j ++)
  {
    int c; scanf("%d", &c);
    for (int i = 0; i < c; i ++)
    {
      if (mat[i][j] == 0) valid = false;
      mat[i][j] = 1;
    }
    if (c < n)
    {
      if (mat[c][j] == 1) valid = false;
      mat[c][j] = 0;
    }
  }

  lli sum = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      sum += mat[i][j] == -1;
  printf("%lld\n", valid == 0 ? 0 : modExp(2, sum));

  return 0;
}
