#include <bits/stdc++.h>
using namespace std;

const int misMatchPenalty = 3, gapPenalty = 2, maxStringSize = 1e4;
char stringA[maxStringSize + 1], stringB[maxStringSize + 1], finalA[2*maxStringSize + 1], finalB[2*maxStringSize + 1];
int stringASize, stringBSize, finalASize, finalBSize;
int dp[2*maxStringSize + 1][2*maxStringSize + 1];

void getMinimumPenalty()
{
  for (int i = 0; i <= stringASize + stringBSize; i ++) dp[i][0] = dp[0][i] = i * gapPenalty;
  for (int i = 1; i <= stringASize; i ++)
    for (int j = 1; j <= stringBSize; j ++)
      if (stringA[i - 1] == stringB[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else
        dp[i][j] = min({dp[i - 1][j - 1] + misMatchPenalty,
                        dp[i - 1][j] + gapPenalty,
                        dp[i][j - 1] + gapPenalty});
}

void buildSolution()
{
  int i = stringASize, j = stringBSize, finalSize = stringASize + stringBSize;
  while (i && j)
  {
    if (stringA[i - 1] == stringB[j - 1] || dp[i - 1][j - 1] + misMatchPenalty == dp[i][j])
      finalA[finalASize ++] = stringA[-- i], finalB[finalBSize ++] = stringB[-- j];
    else if (dp[i - 1][j] + gapPenalty == dp[i][j])
      finalA[finalASize ++] = stringA[-- i], finalB[finalBSize ++] = '_';
    else
      finalA[finalASize ++] = '_', finalB[finalBSize ++] = stringB[-- j];
  }
  while (finalASize < finalSize) { finalA[finalASize ++] = '_'; finalA[finalASize] = '\0'; }
  while (finalBSize < finalSize) { finalB[finalBSize ++] = '_'; finalB[finalBSize] = '\0'; }
  reverse(finalA, finalA + finalASize), reverse(finalB, finalB + finalBSize);
}

int main()
{
  scanf("%[^\n]\n%[^\n]", stringA, stringB);
  stringASize = strlen(stringA), stringBSize = strlen(stringB);
  getMinimumPenalty();
  buildSolution();
  printf("To align:\n\t%s\n\t%s\n", stringA, stringB);
  printf("Minimum Penalty in aligning: %d\n", dp[stringASize][stringBSize]);
  printf("\t%s\n\t%s\n", finalA, finalB);
  return(0);
}