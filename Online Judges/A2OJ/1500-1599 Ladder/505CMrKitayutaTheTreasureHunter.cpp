#include <bits/stdc++.h>
using namespace std;
int n, d, lastLocation = 0, location[(int) 3e4 + 1];
int dp[(int) 3e4 + 1][500];
// 500 because he can only offset from d by less then 250
// since 1 + ... + 250 == (250*(250-1)) / 2 > 30000

int solve(int i, int prev)
{
  if (i > lastLocation || prev <= 0) return(0);

  int offset = prev - d + 250;
  if (dp[i][offset] == -1)
  {
    int ans = max(solve(i + prev, prev), max(solve(i + prev - 1, prev - 1), solve(i + prev + 1, prev + 1)));
    dp[i][offset] = ans + location[i];
  }
  return(dp[i][offset]);
}

int main()
{
  memset(location, 0, sizeof(location));
  memset(dp, -1, sizeof(dp));
  scanf("%d %d", &n, &d);
  for (int i = 0, loc; i < n; i ++)
  {
    scanf("%d", &loc); lastLocation = max(lastLocation, loc);
    location[loc] ++;
  }

  int ans = solve(d, d);
  printf("%d\n", ans);
  return(0);
}