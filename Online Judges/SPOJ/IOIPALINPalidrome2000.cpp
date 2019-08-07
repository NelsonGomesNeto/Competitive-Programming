#include <bits/stdc++.h>
using namespace std;
int dp[5001][5001];

int biggest(int i, int j, char s[], char rev[])
{
  if (!s[i] || !rev[j]) return(0);

  if (dp[i][j] == -1)
  {
    if (s[i] == rev[j])
      dp[i][j] = 1 + biggest(i + 1, j + 1, s, rev);
    else
      dp[i][j] = max(biggest(i + 1, j, s, rev), biggest(i, j + 1, s, rev));
  }
  return(dp[i][j]);
}

int botup(int n, char s[], char rev[])
{
  for (int i = n; i >= 0; i --)
    for (int j = n; j >= 0; j --)
    {
      if (s[i] == '\0' || rev[j] == '\0') dp[i][j] = 0;
      else if (s[i] == rev[j]) dp[i][j] = 1 + dp[i + 1][j + 1];
      else dp[i][j] = max(dp[i + 1][j], dp[i][j  + 1]);
    }
  return(dp[0][0]);
}

int main()
{
  //memset(dp, -1, sizeof(dp));
  int n; scanf("%d", &n);
  char s[n + 1], rev[n + 1]; scanf("%s", s);
  for (int i = 0; s[i]; i ++)
    rev[i] = s[n - 1 - i];
  s[n] = rev[n] = '\0';

  int ans = n - botup(n, s, rev);//biggest(0, 0, s, rev);
  printf("%d\n", ans);

  return(0);
}