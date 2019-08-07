#include <stdio.h>

int main()
{
  int pessoas, tempo = 0, tempoanterior = 0, total = 0;
  scanf("%i", &pessoas);
  while (pessoas > 0)
  {
    tempoanterior = tempo;
    scanf("%i", &tempo);
    if (tempo - tempoanterior > 10 || tempoanterior == 0)
    {
      total += 10;
    }
    else
    {
      total += tempo - tempoanterior;
    }
    pessoas --;
  }
  printf("%i\n", total);
  return(0);
}
