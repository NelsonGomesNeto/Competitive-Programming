#include <bits/stdc++.h>
using namespace std;
int dp[100][300*100 + 1];

int can(int s[], int i, int size, int now, int target)
{
  if (i == size) return(now == target);

  if (dp[i][now] == -1)
    dp[i][now] = can(s, i + 1, size, abs(now - s[i]), target) || can(s, i + 1, size, abs(now + s[i]), target);

  return(dp[i][now]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  int s[100], size = 0; char end;
  while (scanf("%d%c", &s[size ++], &end) && end != '\n');
  int target; scanf("%d", &target);

  printf("%s\n", can(s, 0, size, 0, target) ? "Yes" : "No");

  return(0);
}