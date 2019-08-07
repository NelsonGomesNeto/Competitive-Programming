#include <stdio.h>

int main()
{
  int n, repeat, ingresso, winner, teste = 1;
  while (scanf("%d", &n) && n != 0)
  {
    for (repeat = 0; repeat < n; repeat ++)
    {
      scanf("%d", &ingresso);
      if (ingresso == repeat + 1)
      {
        winner = ingresso;
      }
    }
    printf("Teste %d\n%d\n\n", teste, winner);
    teste ++;
  }
  return(0);
}
