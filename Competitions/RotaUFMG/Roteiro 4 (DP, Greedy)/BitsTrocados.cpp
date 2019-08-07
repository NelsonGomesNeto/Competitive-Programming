#include <bits/stdc++.h>
int dc[4] = {50, 10, 5, 1};

void coinChange(int change[], int money)
{
  for (int i = 0; i < 4; i ++)
  {
    change[i] = money / dc[i];
    money %= dc[i];
  }
}

int main()
{
  int v, t = 0;
  while (scanf("%d", &v) && v)
  {
    if (t ++) printf("\n");
    int change[4]; memset(change, 0, sizeof(change));
    coinChange(change, v);

    printf("Teste %d\n", t);
    for (int i = 0; i < 4; i ++)
      printf("%d%c", change[i], i < 4 - 1 ? ' ' : '\n');
  }
  return(0);
}