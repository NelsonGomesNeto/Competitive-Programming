#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int tubes[2][maxN];

int memo[2][maxN][2];
bool dfs(int i, int j = 0, bool fromLeft = true)
{
  // printf("%d %d\n", i, j);
  if (j == n) return i == 1;
  if (memo[i][j][fromLeft] == -1)
  {
    // memo[i][j][fromLeft] = false;
    bool ans = false;
    if (tubes[i][j] <= 2 && fromLeft)
      ans = dfs(i, j + 1, true);
    if (tubes[i][j] >= 3)
    {
      if (fromLeft)
        ans = dfs(1 - i, j, false);
      else
        ans = dfs(i, j + 1, true);
    }
    memo[i][j][fromLeft] = ans;
  }
  return memo[i][j][fromLeft];
}

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d", &n);
    for (int i = 0; i < 2; i ++)
      for (int j = 0; j < n; j ++)
      {
        scanf("%1d", &tubes[i][j]);
        memo[i][j][0] = memo[i][j][1] = -1;
      }

    bool ans = dfs(0);
    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}
