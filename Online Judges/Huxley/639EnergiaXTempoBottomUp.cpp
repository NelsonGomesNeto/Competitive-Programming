#include <bits/stdc++.h>
using namespace std;
int dp[5000][20], theLevel[5000], program[5000][20];

int topDown(int i, int p, int k, int f, int shift)
{
  if (i == p) return(0);
  if (dp[i][k] == -1)
  {
    int ans = topDown(i + 1, p, k, f, shift) + program[i][k];
    for (int j = 0; j < f; j ++)
      if (j != k) ans = min(ans, topDown(i + 1, p, j, f, shift) + program[i][j] + shift);
    dp[i][k] = ans;
  }
  return(dp[i][k]);
}

int bottomUp(int p, int f, int shift)
{
  for (int i = 0; i < f; i ++) dp[0][i] = program[0][i] + (i > 0) * shift;
  for (int i = 1; i < p; i ++)
  {
    for (int j = 0; j < f; j ++)
      dp[i][j] = dp[i - 1][j] + program[i][j];

    for (int j = 0; j < f; j ++)
      for (int k = 0; k < f; k ++)
        if (j != k)
          dp[i][k] = min(dp[i][k], dp[i - 1][j] + program[i][k] + shift);
  }
  for (int i = 0; i < f; i ++)
    dp[p - 1][0] = min(dp[p - 1][0], dp[p - 1][i]);
  return(dp[p - 1][0]);
}

int main()
{
  int f, p, e, a;
  while (scanf("%d %d %d %d", &f, &p, &e, &a) && !(!f && !p && !e && !a))
  {
    int shift = e * a;
    int pe, pa;
    for (int i = 0; i < p; i ++)
      for (int j = 0; j < f; j ++)
      {
        scanf("%d %d", &pe, &pa);
        program[i][j] = pe * pa;
      }

    //memset(dp, -1, sizeof(dp));
    //int ans = topDown(0, p, 0, f, shift);
    int ans = bottomUp(p, f, shift);
    printf("%d\n", ans);
  }

  return(0);
}