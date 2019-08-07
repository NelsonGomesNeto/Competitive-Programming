#include <bits/stdc++.h>
using namespace std;
int dp[5001][5001];

int lcs(char s[], char r[], int i, int j, int size)
{
  if (i >= size || j >= size) return(0);
  if (dp[i][j] == -1)
  {
    int best = 0;
    if (s[i] == r[j])
      best = lcs(s, r, i + 1, j + 1, size) + 1;
    else
      best = max(lcs(s, r, i + 1, j, size), lcs(s, r, i, j + 1, size));
    dp[i][j] = best;
  }
  return(dp[i][j]);
}

int lcsBot(char s[], char r[], int size)
{
  for (int i = size; i >= 0; i --)
    for (int j = size; j >= 0; j --)
    {
      if (!s[i] || !r[j]) dp[i][j] = 0;
      else if (s[i] == r[j]) dp[i][j] = 1 + dp[i + 1][j + 1];
      else dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
    }
  return(dp[0][0]);
}

int main()
{
  int size; scanf("%d", &size);
  char s[size + 1], r[size + 1]; scanf("\n%s", s);
  for (int i = 0; i < size; i ++) r[size - i - 1] = s[i];
  r[size] = '\0';

  //memset(dp, -1, sizeof(dp));
  int ans = lcsBot(s, r, size);
  printf("%d\n", size - ans);
  return(0);
}