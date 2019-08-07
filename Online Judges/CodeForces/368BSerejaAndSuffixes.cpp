#include <bits/stdc++.h>

int dp[100005];

int main()
{
  memset(dp, 0, sizeof(dp));
  int n, m; scanf("%d %d", &n, &m);
  int array[n];
  for (int i = 0; i < n; i ++) scanf("%d", &array[i]);

  int distinct = 0, ans[n];
  for (int i = n - 1; i >= 0; i --)
  {
    distinct += !dp[array[i]];
    ans[i] = distinct;
    dp[array[i]] = 1;
  }

  int query;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d", &query);
    printf("%d\n", ans[query - 1]);
  }

  return(0);
}