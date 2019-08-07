#include <stdio.h>

int main()
{
  int k; long double serie, conta;
  while (scanf("%d", &k) && k != -1)
  {
    serie = 0; conta = 1;
    while (serie <= k)
    {
      serie += 1 / conta;
      conta ++;
    }
    conta --;
    printf("%.Lf\n", conta);
  }
  return(0);
}
