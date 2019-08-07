#include <bits/stdc++.h>
using namespace std;
int dp[1000][2];

int find(int i, int k, int target, int d, int done)
{
  if (i == target && done) return(1);
  else if (i >= target) return(0);

  if (dp[i][done] == -1)
  {
    int n, total = 0;
    for (n = 1; n <= k; n ++)
    {
      total += find(i + n, k, target, d, done || n >= d);
      total %= 1000000007;
    }
    dp[i][done] = total;
  }
  return(dp[i][done]);
}

int main()
{
  int n, k, d; scanf("%d %d %d", &n, &k, &d);

  memset(dp, -1, sizeof(dp));
  int answer = find(0, k, n, d, 0);

  printf("%d\n", answer);

  return(0);
}