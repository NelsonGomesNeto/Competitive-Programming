#include <bits/stdc++.h>
using namespace std;

int binpack(int a[], int i, int end, int dp[])
{
  if (i >= end) return(0);

  if (dp[i] == -1)
  {
    int ans = binpack(a, i + 1, end, dp);
    ans = max(ans, binpack(a, i + 2, end, dp) + a[i]);
    dp[i] = ans;
  }
  return(dp[i]);
}

int main()
{
  int y, x;
  while (scanf("%d %d", &y, &x) && !(!y && !x))
  {
    int mat[y][x], line[y], dp[max(y, x)];
    for (int i = 0; i < y; i ++)
    {
      for (int j = 0; j < x; j ++)
      {
        scanf("%d", &mat[i][j]);
        dp[j] = -1;
      }
      line[i] = binpack(mat[i], 0, x, dp);
    }
    memset(dp, -1, sizeof(dp));
    int candies = binpack(line, 0, y, dp);
    printf("%d\n", candies);
  }
  return(0);
}