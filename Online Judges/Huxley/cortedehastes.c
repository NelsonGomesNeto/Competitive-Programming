#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define memCard pd[tam]

int haste;

int max(int a, int b)
{
  return(a > b ? a : b);
}

int dp(int pd[], int p[], int tam)
{
  if (tam == haste)
    return(0);

  if (memCard == -1)
  {
    int i;
    memCard = INT_MIN;
    
    for (i = 1; i <= haste - tam; i ++)
      memCard = max(memCard, dp(pd, p, tam + i) + p[i]);
  }
  return(memCard);
}

int main()
{
  while (scanf("%d", &haste) && haste != 0)
  {
    int preco[haste + 1], DP[haste + 1], i;
    memset(DP, -1, (haste + 1) * sizeof(int));

    for (i = 1; i <= haste; i ++)
      scanf("%d", &preco[i]);

    int ans = dp(DP, preco, 0);
    printf("%d\n", ans);
  }
  return(0);
}
