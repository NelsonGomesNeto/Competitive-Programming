#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3 + 3; int n, m;
const int mid = maxN - 1;
char s[maxN][maxN + 1];
const lli mod = 1e9 + 7;
set<int> columns[maxN], rows[maxN], diagonals[2*maxN];

int di[3] = {0, 1, 1}, dj[3] = {1, 1, 0};
lli memo[maxN][maxN];
lli suffix[3][maxN + 3][maxN + 3];
lli solve(int i, int j);
lli suff(int k, int i, int j)
{
  if (i >= n || j >= m || s[i][j] == '#') return 0;
  lli &ans = suffix[k][i][j];
  if (ans != -1) return ans;
  return ans = (suff(k, i + di[k], j + dj[k]) + solve(i, j)) % mod;
}
lli solve(int i = 0, int j = 0)
{
  if (i >= n || j >= m || s[i][j] == '#') return 0;
  if (i == n - 1 && j == m - 1) return 1;
  lli &ans = memo[i][j];
  if (ans != -1) return ans;

  ans = 0;
  for (int k = 0; k < 3; k++)
  {
    int end = 0;
    if (k == 0) // horizontal
      end = *rows[i].upper_bound(j) - j;
    else if (k == 1) // diagonal
      end = *diagonals[i - j + mid].upper_bound(j) - j;
    else if (k == 2) // vertical
      end = *columns[j].upper_bound(i) - i;

    int d = end;
    int ni = i + d*di[k], nj = j + d*dj[k];
    ans = (ans + suff(k, i + di[k], j + dj[k]) - suff(k, ni, nj) + mod) % mod;

    // for (int d = 1; ; d++)
    // {
    //   int ni = i + d*di[k], nj = j + d*dj[k];
    //   lli res = solve(ni, nj);
    //   if (res == 0) break;
    //   ans = (ans + res) % mod;
    // }
    // ans = (ans + now) % mod;
  }

  return ans;
}

lli solve2()
{
  memset(memo, 0, sizeof(memo));
  memset(suffix, 0, sizeof(suffix));
  memo[n - 1][m - 1] = 1;
  for (int k = 0; k < 3; k++)
    suffix[k][n - 1][m - 1] = 1;

  for (int i = n - 1; i >= 0; i--)
    for (int j = m - 1; j >= 0; j--)
      if (s[i][j] != '#')
      {
        for (int k = 0; k < 3; k++)
        {
          int end = 0;
          if (k == 0) // horizontal
            end = *rows[i].upper_bound(j) - j;
          else if (k == 1) // diagonal
            end = *diagonals[i - j + mid].upper_bound(j) - j;
          else if (k == 2) // vertical
            end = *columns[j].upper_bound(i) - i;

          int d = end;
          int ni = i + d*di[k], nj = j + d*dj[k];
          lli now = 0;
          now = (suffix[k][i + di[k]][j + dj[k]]
               - suffix[k][ni][nj]
               + mod) % mod;

          // for (int d = 1; d < end; d++)
          // {
          //   int ni = i + d*di[k], nj = j + d*dj[k];
          //   memo[i][j] = (memo[i][j] + memo[ni][nj]) % mod;
          // }

          memo[i][j] = (memo[i][j] + now) % mod;
        }

        for (int k = 0; k < 3; k++)
        {
          int ni = i + di[k], nj = j + dj[k];
          suffix[k][i][j] = (suffix[k][ni][nj] + memo[i][j]) % mod;
        }
      }
  return memo[0][0];
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++) rows[i].clear();
    for (int j = 0; j < m; j++) columns[j].clear();
    for (int ij = -(m - 1); ij < n; ij++) diagonals[ij + mid].clear();

    for (int i = 0; i < n; i++)
      scanf(" %s", s[i]);

    for (int i = 0; i < n; i++)
    {
      rows[i].insert(m);
      for (int j = 0; j < m; j++)
        if (s[i][j] == '#')
          rows[i].insert(j);
    }
    for (int j = 0; j < m; j++)
    {
      columns[j].insert(n);
      for (int i = 0; i < n; i++)
        if (s[i][j] == '#')
          columns[j].insert(i);
    }
    for (int ij = -(m - 1); ij < n; ij++)
    {
      int i, j;
      if (ij == 0) i = 0, j = 0;
      else if (ij < 0) i = 0, j = -ij;
      else i = ij, j = 0;

      diagonals[ij + mid].insert(m);
      for (int d = 0; ; d++)
      {
        int ni = i + d*di[1], nj = j + d*dj[1];
        if (ni >= n || nj >= m || s[ni][nj] == '#')
        {
          diagonals[ij + mid].insert(nj);
          break;
        }
      }
    }

    memset(memo, -1, sizeof(memo));
    memset(suffix, -1, sizeof(suffix));
    lli ans = solve();
    // lli ans = solve2();
    printf("%lld\n", ans);
  }
  return 0;
}