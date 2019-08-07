#include <stdio.h>
#include <string.h>
#define memCard pd[i][energia]
#define naoCome dp(pd, food, i + 1, energia)
#define come dp(pd, food, i + 1, energia + food[i]) + food[i]

int comidas;

int max(int a, int b)
{
  return(a > b ? a : b);
}

int dp(int pd[][481], int food[], int i, int energia)
{
  if (i == comidas)
    return(0);
  if (memCard == -1)
  {
    memCard = naoCome;
    if (energia + food[i] <= 480)
      memCard = max(memCard, come);
  }
  return(memCard);
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    scanf("%d", &comidas);
    int comida[comidas], i, DP[comidas][481];
    for (i = 0; i < comidas; i ++)
    {
      scanf("%d", &comida[i]);
      memset(DP[i], -1, 481 * sizeof(int));
    }
    int ans = dp(DP, comida, 0, 0);
    printf("%d\n", ans);
    tests --;
  }
  return(0);
}
