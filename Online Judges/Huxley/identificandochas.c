#include <stdio.h>

int main()
{
  int cha, competidor, winner = 0, repeat;
  scanf("%d", &cha);
  for (repeat = 0; repeat < 5; repeat ++)
  {
    scanf("%d", &competidor);
    if (cha == competidor)
      winner ++;
  }
  printf("%d\n", winner);
  return(0);
}
