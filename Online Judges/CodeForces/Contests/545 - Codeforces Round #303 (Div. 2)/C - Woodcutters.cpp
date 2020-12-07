#include <bits/stdc++.h>
using namespace std;
int dp[100001][3];

int bt(int tree[][2], int i, int n, int blocked, int done)
{
  if (i >= n) return(0);

  if (dp[i][done] == -1)
  {
    int ans = bt(tree, i + 1, n, tree[i][0], 0);
    if (blocked < tree[i][0] - tree[i][1]) ans = max(ans, 1 + bt(tree, i + 1, n, tree[i][0], 1));
    if (tree[i+1][0] > tree[i][0] + tree[i][1]) ans = max(ans, 1 + bt(tree, i + 1, n, tree[i][0] + tree[i][1], 2));
    dp[i][done] = ans;
  }

  return(dp[i][done]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  int n; scanf("%d", &n);
  int tree[n][2];
  for (int i = 0; i < n; i ++)
    scanf("%d %d", &tree[i][0], &tree[i][1]);

  int ans = (n >= 2 ? 2 : n) + bt(tree, 1, n - 1, tree[0][0], 0);

  printf("%d\n", ans);

  return(0);
}