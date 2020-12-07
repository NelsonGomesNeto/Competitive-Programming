#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int
int n, m, k; lli inf = 1e18, dp[5000][5000], sum[5001];

lli lol(int array[], int i, int j)
{
  if (i >= n || j == k) return(j == k ? 0 : -inf);

  if (dp[i][j] == -1)
  {
    lli ans = lol(array, i + 1, j);
    if (j < k && i + m <= n)
      ans = max(ans, (sum[i + m] - sum[i]) + lol(array, i + m, j + 1));
    dp[i][j] = ans;
  }
  return(dp[i][j]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  scanf("%d %d %d", &n, &m, &k);
  int array[n]; lli s = 0; sum[0] = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &array[i]); s += array[i];
    sum[i + 1] = s;
  }
  DEBUG for (int i = 0; i <= n; i ++) printf("%lld%c", sum[i], i < n ? ' ' : '\n');

  lli maxSum = lol(array, 0, 0);
  printf("%lld\n", maxSum);
  return(0);
}