#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, m;
const int inf = 1e6;
char mat[maxN][maxN + 1];
int si, sj, walls = 0;
char aux[5];


int di[4] = {0, 0, -1, 1}, dj[4] = {-1, 1, 0, 0};
int dia[4] = {-1, -1, 1, 1}, dja[4] = {1, -1, 1, -1};
bool valid(int i, int j)
{
  return i >= 0 && j >= 0 && i < n && j < m && mat[i][j] == '.';
}
bool validPos(int i, int j)
{
  return i >= 0 && j >= 0 && i < n && j < m;
}
bool canPutTable(int i, int j)
{
  if (mat[i][j] != '.') return false;
  for (int k = 0; k < 4; k++)
  {
    int ni = i + di[k], nj = j + dj[k];
    if (validPos(ni, nj) && mat[ni][nj] == 't') return false;
    if (validPos(ni, nj) && mat[ni][nj] == 'S') return false;
    // int sum = 0;
    // for (int kk = 0; kk < 4; kk++)
    // {
    //   int nni = ni + di[k], nnj = nj + dj[k];
    //   sum += validPos(nni, nnj) && mat[nni][nnj] == 't';
    // }
    // if (sum >= 1) return false;
  }
  for (int k = 0; k < 4; k++)
  {
    int ni = i + dia[k], nj = j + dja[k];
    if (validPos(ni, nj) && mat[ni][nj] == 't') return false;
  }
  return true;
}
int getChairs(int i, int j)
{
  int total = 0;
  for (int k = 0; k < 4; k++)
  {
    int ni = i + di[k], nj = j + dj[k];
    total += valid(ni, nj);
  }
  return total;
}
bool visited[maxN][maxN];
int check(int i = si, int j = sj)
{
  if (i < 0 || j < 0 || i >= n || j >= m) return false;
  if (visited[i][j]) return false;
  visited[i][j] = true;
  if (mat[i][j] == 't') return true;
  if (mat[i][j] != '.' && mat[i][j] != 'S') return false;

  int ans = 0;
  for (int k = 0; k < 4; k++)
    ans += check(i + di[k], j + dj[k]);
  return ans;
}
bool check2()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (mat[i][j] == '.')
      {
        bool hasout = false;
        for (int k = 0; k < 4; k++)
        {
          int ni = i + di[k], nj = j + dj[k];
          if (validPos(ni, nj) && mat[ni][nj] == '.')
            hasout = true;
          if (validPos(ni, nj) && mat[ni][nj] == 'S')
            hasout = true;
        }
        if (!hasout) return false;
      }
  return true;
}
int solve(int i = 0, int j = 0, int tables = 0)
{
  if (i == n)
  {
    memset(visited, false, sizeof(visited));
    bool can = check() == tables && check2();
    DEBUG
      if (can)
      {
        for (int a = 0; a < n; a++)
          printf("%s\n", mat[a]);
        printf("-----------\n");
      }
    return can ? 0 : -inf;
  }

  int ans = solve(i + (j == m - 1), (j + 1) % m, tables);
  if (canPutTable(i, j))
  {
    mat[i][j] = 't';
    int chairs = getChairs(i, j);
    ans = max(ans, chairs + solve(i + (j == m - 1), (j + 1) % m, tables + 1));
    mat[i][j] = '.';
  }
    
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    walls = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%s", mat[i]);
      for (int j = 0; j < m; j++)
      {
        if (mat[i][j] == 'S')
          si = i, sj = j;
        walls += mat[i][j] == '#';
      }
    }

    int ans = solve();
    ans = max(ans, 0);
    printf("%d\n", ans);
  }
  return 0;
}