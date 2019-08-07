#include <bits/stdc++.h>
using namespace std;
int dp[101][101];

int play(int a1, int a2)
{
  if (a1 <= 0 || a2 <= 0 || (a1 == 1 && a2 == 1)) return(0);
  if (dp[a1][a2] == -1)
    dp[a1][a2] = max(1 + play(a1 - 2, a2 + 1), 1 + play(a1 + 1, a2 - 2));
  return(dp[a1][a2]);
}

int playGreedy(int a1, int a2)
{
  if (a1 <= 0 || a2 <= 0 || (a1 == 1 && a2 == 1)) return(0);
  if (a1 < a2)
    return(1 + play(a1 + 1, a2 - 2));
  else
    return(1 + play(a1 - 2, a2 + 1));
}

int main()
{
  memset(dp, -1, sizeof(dp));
  int a1, a2; scanf("%d %d", &a1, &a2);

  int ans = playGreedy(a1, a2);

  printf("%d\n", ans);

  return(0);
}