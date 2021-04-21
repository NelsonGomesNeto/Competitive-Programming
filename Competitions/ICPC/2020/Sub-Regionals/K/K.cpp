#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli mod = 2;

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

vector<vector<lli>> mat;
vector<lli> ans;

const int maxN = 1e2, maxM = 1e4; int n, m;
vector<int> graph[maxN];

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++)
  {
    int u, v; scanf("%d %d", &u, &v); u--, v--;
    graph[u].push_back(v), graph[v].push_back(u);
  }

  mat.resize(n, vector<lli>(n + 1));
  for (int u = 0; u < n; u++)
    if (graph[u].size() & 1)
    {
      mat[u][u] = 1;
      for (int v: graph[u])
        mat[u][v] = 1;
      mat[u][n] = 0;
    }
    else
    {
      for (int v: graph[u])
        mat[u][v] = 1;
      mat[u][n] = 1;
    }

  bool can = gauss(mat, ans) > 0;
  printf("%s\n", can ? "Y" : "N");

  return 0;
}