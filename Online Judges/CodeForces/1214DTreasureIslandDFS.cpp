#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxV = 2e6, inf = 1e9;
int n, m;
vector<vector<char>> mat;

bool dfs(int i = 0, int j = 0)
{
  if (i < 0 || j < 0 || i >= n || j >= m || mat[i][j] == '#') return false;
  if (i == n - 1 && j == m - 1) return true;
  mat[i][j] = '#';
  return dfs(i + 1, j) || dfs(i, j + 1);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    mat.clear();
    mat.resize(n);
    for (int i = 0; i < n; i ++)
    {
      getchar();
      mat[i].resize(m + 1);
      for (int j = 0; j < m; j ++)
        scanf("%c", &mat[i][j]);
    }

    int ans = 0;
    while (dfs())
    {
      ans ++;
      mat[0][0] = mat[n - 1][m - 1] = '.';
    }

    printf("%d\n", ans);
  }
  return(0);
}
