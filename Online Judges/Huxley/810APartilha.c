#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
  return(a > b ? a : b);
}

int bt(int value[], int i, int end, int total, int dp[][end])
{
  if (i == end) return(0);

  if (dp[total][i] == -1)
  {
    int best = bt(value, i + 1, end, total, dp);
    if (total - value[i] >= 0)
      best = max(best, bt(value, i + 1, end, total - value[i], dp) + value[i]);
    dp[total][i] = best;
  }
  return(dp[total][i]);
}

int main()
{
  int run = 0, tests; scanf("%d", &tests);
  while (run ++ < tests)
  {
    int objects; scanf("%d", &objects);
    int value[objects], i, total = 0;
    for (i = 0; i < objects; i ++)
    {
      scanf("%d", &value[i]);
      total += value[i];
    }

    int dp[total][objects]; memset(dp, -1, sizeof(dp));
    int answer = bt(value, 0, objects, total / 2, dp);

    printf("caso %d: %d %d\n", run - 1, answer, total - answer);
  }
  return(0);
}