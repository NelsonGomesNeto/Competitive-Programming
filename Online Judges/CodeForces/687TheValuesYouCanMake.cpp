#include <bits/stdc++.h>
using namespace std;

const int maxN = 501, maxK = 501, inf = 1e3; int n, k;
int coins[maxN], possibleSumSize, possibleSum[maxK]; int memo[maxK][maxK], memo2[maxK][maxK];

int solve(int i, int subSum, int sum)
{
  if (i == n) return(memo[subSum][sum] = (subSum + sum == k));
  if (memo[subSum][sum] == -1 || memo2[subSum][sum] > i)
  {
    int ans = 0;
    ans = max(ans, solve(i + 1, subSum, sum));
    if (subSum + sum + coins[i] <= k)
    {
      ans = max(ans, solve(i + 1, subSum + coins[i], sum));
      ans = max(ans, solve(i + 1, subSum, sum + coins[i]));
    }
    memo[subSum][sum] = ans; memo2[subSum][sum] = min(memo2[subSum][sum], i);
  }
  return(memo[subSum][sum]);
}

bitset<maxK> dp[maxK];
// int dp[maxK][maxK];
void printBitset()
{
  for (int i = 0; i <= k; i ++)
  {
    for (int j = 0; j <= k; j ++) printf("%d", dp[i][j] ? 1 : 0);
    printf("\n");
  }
  printf("\n");
}
void iterativeSolve()
{
  // for (int i = 0; i < n; i ++)
  //   for (int j = k - coins[i]; j >= 0; j --)
  //     for (int m = 0; m <= k; m ++)
  //     {
  //       dp[j + coins[i]][m] |= dp[j][m];
  //       if (m + coins[i] <= k)
  //         dp[j + coins[i]][m + coins[i]] |= dp[j][m];
  //     }
  dp[0][0] = 1;
  // printBitset();
  for (int i = 0; i < n; i ++)
  {
    // printf("%d\n", coins[i]);
    for (int j = k - coins[i]; j >= 0; j --)
      dp[j + coins[i]] |= (dp[j] << coins[i]) | dp[j];
    // printBitset();
  }
}

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i ++) scanf("%d", &coins[i]);
  // sort(coins, coins+n);

  // memset(memo, -1, sizeof(memo)); for (int i = 0; i <= k; i ++) for (int j = 0; j <= k; j ++) memo2[i][j] = inf;
  // solve(0, 0, 0);
  iterativeSolve();
  for (int i = 0; i <= k; i ++)
    // if (memo[i][k - i] == 1)
    if (dp[k][i])
      possibleSum[i] = memo[i][k - i], possibleSumSize += 1;

  printf("%d\n", possibleSumSize);
  for (int i = 0; i <= k; i ++)
    // if (possibleSum[i])
    if (dp[k][i])
      printf("%d ", i);
  printf("\n");
  return(0);
}