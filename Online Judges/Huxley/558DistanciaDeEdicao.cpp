#include <bits/stdc++.h>
using namespace std;
char a[2001], b[2001];
int inf = 1<<20, dp[2001][2001];

int editDistance(int i, int j)
{
  if (!a[i] && !b[j]) return(0);
  if (!a[i]) return(strlen(b) - j);
  if (!b[j]) return(strlen(a) - i);

  if (dp[i][j] == -1)
  {
    int ans = inf;
    if (a[i] == b[j])
      ans = min(ans, editDistance(i + 1, j + 1));
    else
    {
      ans = min(ans, 1 + editDistance(i + 1, j));
      ans = min(ans, 1 + editDistance(i, j + 1));
      ans = min(ans, 1 + editDistance(i + 1, j + 1));
    }
    dp[i][j] = ans;
  }
  return(dp[i][j]);
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests -- > 0)
  {
    memset(dp, -1, sizeof(dp));
    getchar();
    scanf("%s\n%s", a, b);
    int ans = editDistance(0, 0);

    printf("%d\n", ans);
  }
  return(0);
}