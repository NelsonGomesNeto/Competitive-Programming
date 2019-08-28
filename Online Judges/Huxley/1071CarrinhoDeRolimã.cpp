#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n, m;
int di[4] = {0, 0, 1, -1}, dj[4] = {-1, 1, 0, 0};
int mat[maxN][maxN];
int memo[maxN][maxN];
char name[100];

bool valid(int i, int j, int k)
{
  int ni = i + di[k], nj = j + dj[k];
  if (ni < 0 || nj < 0 || ni >= n || nj >= m)
    return false;
  return mat[i][j] > mat[ni][nj];
}
int solve(int i, int j)
{
  if (memo[i][j] == -1)
  {
    int ans = 1;
    for (int k = 0; k < 4; k ++)
      if (valid(i, j, k))
        ans = max(ans, 1 + solve(i + di[k], j + dj[k]));
    memo[i][j] = ans;
  }
  return memo[i][j];
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf(" %s %d %d", name, &n, &m);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        scanf("%d", &mat[i][j]);

    memset(memo, -1, sizeof(memo));
    int ans = 1;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
      {
        ans = max(ans, solve(i, j));
      }
    printf("%s: %d\n", name, ans);
  }
  return(0);
}