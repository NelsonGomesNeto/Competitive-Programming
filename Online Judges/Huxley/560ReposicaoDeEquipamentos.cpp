#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
const int limit = 5010;
int a, n, c, maintenance[limit], sell[limit], junk[limit];
int dp[limit][limit], path[limit][limit];

void read(int a[], int start, int size)
{
  for (int i = start; i < size; i ++) scanf("%d", &a[i]);
}

int solve(int i, int year)
{
  if (i == n) return(-junk[year]);

  if (dp[i][year] == -1)
  {
    int keep = solve(i + 1, year + 1) + maintenance[year];
    int buy = solve(i + 1, 1) - sell[year] + c + maintenance[0];
    if (keep > buy) path[i][year] = 1;
    dp[i][year] = min(keep, buy);
  }

  return(dp[i][year]);
}

void followPath(int action[])
{
  int year = a, cost = 0;
  for (int i = 0; i < n; i ++)
  {
    if (!path[i][year])
    {
      DEBUG printf("%d\n", maintenance[year]);
      cost += maintenance[year];
      action[i] = 1, year ++;
    }
    else
    {
      DEBUG printf("%d %d %d\n", sell[year], c, maintenance[0]);
      cost += -sell[year] + c + maintenance[0];
      year = 1;
    }
  } cost += -junk[year];
  printf("Final cost: %d\n", cost);
} // (-60 + 20 - 10) + (-60 + 30 - 10) + (-20) + (15)

int main()
{
  while (scanf("%d %d %d", &a, &n, &c) != EOF)
  {
    memset(dp, -1, sizeof(dp));
    memset(path, 0, sizeof(path));
    memset(maintenance, 0, sizeof(maintenance));
    memset(sell, 0, sizeof(sell));
    memset(junk, 0, sizeof(junk));

    read(maintenance, 0, n + 2);
    read(sell, 1, n + 2);
    read(junk, 1, n + 2);

    int ans = solve(0, a);
    int action[n]; memset(action, 0, sizeof(action));
    followPath(action);
    printf("%d\n", ans);
    for (int i = 0; i < n; i ++) printf("%c", action[i] ? 'M' : 'B');
    printf("\n");
  }

  return(0);
}
