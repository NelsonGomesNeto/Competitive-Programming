#include <bits/stdc++.h>
#define DEBUG if(0)

int main()
{
  int liters, litersAfter; scanf("%d", &liters);
  litersAfter = liters;

  int cost[9], quantity[9]; memset(quantity, 0, sizeof(quantity));
  int best = 0, num = 0;
  for (int i = 0; i < 9; i ++)
  {
    scanf("%d", &cost[i]);
    int canBuy = liters / cost[i];
    if (canBuy > best)
    {
      litersAfter = liters - (canBuy * cost[i]);
      num = i;
      best = canBuy;
    }
  }
  quantity[num] = best;

  DEBUG printf("%d %d %d\n", num + 1, quantity[num], litersAfter);

  if (quantity[num] > 0)
  {
    for (int at = 9 - 1; at >= 0; at --)
    {
      DEBUG printf("##%d %d %d, at: %d\n", litersAfter, litersAfter + cost[num] - cost[at], quantity[num], at + 1);
      if (litersAfter + cost[num] - cost[at] >= 0 && at > num && quantity[num] > 0)
      {
        DEBUG printf("%d %d\n", at, litersAfter);
        int worthIt = quantity[num];
        if (cost[num] - cost[at] != 0)
          worthIt = (-litersAfter) / (cost[num] - cost[at]);

        DEBUG printf("%d %d %lf\n", worthIt, at + 1, (double) (-litersAfter) / (cost[num] - cost[at]));
        litersAfter = litersAfter + ((cost[num] - cost[at]) * worthIt);
        quantity[at] += worthIt;
        quantity[num] -= worthIt;
      }
    }

    for (int i = 9 - 1; i >= 0; i --)
      for (int j = 0; j < quantity[i]; j ++)
        printf("%d", i + 1);
  }
  else
    printf("-1");

  printf("\n");

  return(0);
}