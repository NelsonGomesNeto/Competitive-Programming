#include <bits/stdc++.h>
using namespace std;
int dp[101][101];

int backTrack(int a[], int b[], int i, int n, int j, int m)
{
  if (i == n || j == m) return(0);

  if (dp[i][j] == -1)
  {
    int ans = (a[i] >= (b[j] - 1)) && (a[i] <= (b[j] + 1));
    if ((a[i] >= (b[j] - 1)) && (a[i] <= (b[j] + 1)))
      ans += backTrack(a, b, i + 1, n, j + 1, m);
    else
      ans += max(backTrack(a, b, i + 1, n, j, m), backTrack(a, b, i, n, j + 1, m));
    dp[i][j] = ans;
  }

  return(dp[i][j]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  int n, m, i;
  scanf("%d", &n); int a[n];
  for (i = 0; i < n; i ++) scanf("%d", &a[i]);
  scanf("%d", &m); int b[m];
  for (i = 0; i < m; i ++) scanf("%d", &b[i]);

  sort(a, a+n); sort(b, b+m);

  int answer = backTrack(a, b, 0, n, 0, m);

  printf("%d\n", answer);

  return(0);
}