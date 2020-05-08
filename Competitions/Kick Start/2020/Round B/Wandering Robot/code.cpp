#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e2; int n, m, l, u, r, d;

struct Block
{
  int n, m; bool bad = false;
};
vector<vector<Block>> mat;

ldouble memo[maxN][maxN];
ldouble solve(int i = 0, int j = 0)
{
  if (i >= u && i <= d && j >= l && j <= r) return 0;
  if (i == n - 1 && j == m - 1) return 1;
  if (memo[i][j] != -1) return memo[i][j];

  ldouble ans = 0;
  if (i < n - 1 && j < m - 1)
  {
    ans = (solve(i + 1, j) + solve(i, j + 1)) / 2;
  }
  else
  {
    if (i == n - 1) ans = solve(i, j + 1);
    if (j == m - 1) ans = solve(i + 1, j);
  }

  return memo[i][j] = ans;
}

ldouble memo2[maxN][maxN];
ldouble solve2(int i = 0, int j = 0)
{
  if (mat[i][j].bad) return 0;
  if (i == mat.size() - 1 && j == mat[0].size() - 1) return 1;
  if (memo2[i][j] != -1) return memo2[i][j];

  ldouble ans = 0;
  if (i < mat.size() - 1 && j < mat[0].size() - 1)
  {
    ans = (mat[i][j].m * solve2(i + 1, j) + mat[i][j].n * solve2(i, j + 1)) / (mat[i][j].n + mat[i][j].m);
  }
  else
  {
    if (i == mat.size() - 1) ans = mat[i][j].n * solve2(i, j + 1);
    if (j == mat[0].size() - 1) ans = mat[i][j].m * solve2(i + 1, j);
  }

  return memo2[i][j] = ans;
}

bool inside(int loi, int loj, int hii, int hij, int i, int j)
{
  return i >= loi && i <= hii && j >= loj && j <= hij;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    mat.clear();
    scanf("%d %d %d %d %d %d", &n, &m, &l, &u, &r, &d);
    swap(n, m);
    l--, u--, r--, d--;
    for (int i = 0; i < maxN; i++)
      for (int j = 0; j < maxN; j++)
        memo[i][j] = memo2[i][j] = -1;

    set<int> cols;
    for (int j = 0; j < m; j += maxN)
      cols.insert(j);
    cols.insert(m - 1);
    cols.insert(m);
    if (l - 1 >= 0) cols.insert(l - 1);
    cols.insert(r);

    set<int> rws;
    for (int i = 0; i < n; i += maxN)
      rws.insert(i);
    rws.insert(n - 1);
    rws.insert(n);
    if (u - 1 >= 0) rws.insert(u - 1);
    rws.insert(d);

    vector<int> columns; for (int i: cols) columns.push_back(i);
    vector<int> rows; for (int i: rws) rows.push_back(i);
    DEBUG {
      for (int i = 0; i < columns.size(); i++)
        printf("%d%c", columns[i], i < columns.size() - 1 ? ' ' : '\n');
    }

    mat.resize(rows.size() - 1);
    for (int i = 0, rr = 0; i < rows.size() - 1; i++)
    {
      for (int j = 0, cc = 0; j < columns.size() - 1; j++)
      {
        mat[i].push_back(Block{rows[i + 1] - rr, columns[j + 1] - cc, inside(u, l, d, r, rr, cc)});
        DEBUG printf("\t%d %d\n", rr, cc);
        cc = columns[j + 1];
      }
      rr = rows[i + 1];
    }
    DEBUG {
      for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[0].size(); j++)
          printf("(%d %d || %d, %d, %d)%c", i, j, mat[i][j].n, mat[i][j].m, mat[i][j].bad, j < mat[0].size() - 1 ? ' ' : '\n');
    }

    ldouble ans = solve2();
    printf("Case #%d: %.12Lf\n", tt, ans);
  }
  return 0;
}