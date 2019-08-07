#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
char words[2][100][31];
int dp[100][100], path[100][100], w[2];

int lcs(int i, int j)
{
  if (i >= w[0] || j >= w[1]) return(0);
  if (dp[i][j] == -1)
  {
    if (!strcmp(words[0][i], words[1][j])) dp[i][j] = 1 + lcs(i + 1, j + 1), path[i][j] = 0;
    else
    {
      int left = lcs(i + 1, j), right = lcs(i, j + 1);
      if (left >= right) dp[i][j] = left, path[i][j] = 1;
      else dp[i][j] = right, path[i][j] = 2;
    }
  }
  return(dp[i][j]);
}

void printLCS()
{
  DEBUG
    for (int i = 0; i < w[0]; i ++)
      for (int j = 0; j < w[1]; j ++)
        printf("%3d%c", dp[i][j], j < w[1] - 1 ? ' ' : '\n');
  for (int i = 0, j = 0, first = 1; i < w[0] && j < w[1];)
  {
    if (path[i][j] == 0) { if (!first) printf(" "); printf("%s", words[0][i]), first = 0; i ++, j ++; }
    if (path[i][j] == 1) i ++; if (path[i][j] == 2) j ++;
  } printf("\n");
}

int main()
{
  while (scanf("%s", words[0][0]) != EOF)
  {
    w[0] = 1, w[1] = 0;
    for (int i = 0; i < 2; i ++)
      while (scanf("%s", words[i][w[i]]) && strcmp(words[i][w[i]], "#")) w[i] ++;

    DEBUG
      for (int j = 0; j < 2; j ++)
        for (int i = 0; i < w[j]; i ++)
        printf("%s%c", words[j][i], i < w[j] - 1 ? ' ' : '\n');

    memset(dp, -1, sizeof(dp));
    int ans = lcs(0, 0);
    DEBUG printf("%d\n", ans);
    printLCS();
    memset(words, '\0', sizeof(words));
  }
  return(0);
}