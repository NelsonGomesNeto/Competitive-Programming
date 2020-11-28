#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli mod;

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

int gauss(vector<vector<lli>> a, vector<lli> &ans)
{
  int n = a.size(), m = a[0].size() - 1;

  vector<int> where(m, - 1);
  for (int col = 0, row = 0; col < m && row < n; col++)
  {
    int sel = row;
    for (int i = row; i < n; i++)
      if (a[i][col] > a[sel][col])
        sel = i;

    if (a[sel][col] == 0)
      continue;

    for (int j = col; j <= m; j++)
      swap(a[sel][j], a[row][j]);
    where[col] = row;

    for (int i = 0; i < n; i++)
      if (i != row)
      {
        lli c = a[i][col] * inv(a[row][col]) % mod;
        for (int j = col; j <= m; j++)
          a[i][j] = (a[i][j] - a[row][j] * c % mod + mod) % mod;
      }

    row++;
  }

  ans.resize(m, 0);
  for (int i = 0; i < m; i++)
    if (where[i] != -1)
      ans[i] = a[where[i]][m] / a[where[i]][i];
  for (int i = 0; i < n; i++)
  {
    lli sum = 0;
    for (int j = 0; j < m; j++)
      sum = (sum + ans[j] * a[i][j] % mod) % mod;
    sum = (sum - a[i][m] + mod) % mod;
    if (sum != 0)
      return 0;
  }

  for (int i= 0; i < m; i++)
    if (where[i] == -1)
      return 2;
  return 1;
}

const int maxN = 1e2; int n, m;
vector<vector<lli>> mat;
vector<lli> ans;

int main()
{
  while (scanf("%d %d %lld", &n, &m, &mod) != EOF)
  {
    mat.resize(n, vector<lli>(m + 1));
    for (int i = 0; i < n; i++)
      for (int j = 0; j <= m; j++)
        scanf("%lld", &mat[i][j]);

    int solutions = gauss(mat, ans);
    printf("Solutions: %s\n", solutions == 0 ? "ZERO" : solutions == 1 ? "ONE" : "INF");
    for (int i = 0; i < m; i++)
      printf("x_%d: %lld\n", i, ans[i]);
  }
  return 0;
}