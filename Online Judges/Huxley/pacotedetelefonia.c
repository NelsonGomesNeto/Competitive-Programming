#include <stdio.h>

int main()
{
  int min = 1, totalmin = 0, lig = 0, limit = 0, totalminlig = 40;
  float preco = 10;
  while (scanf("%d", &min) && min != 0)
  {
    lig ++;
    totalmin += min;
    if (lig > 10 || totalmin > 40)
    {
      if (lig > 10)
      {
        totalminlig = totalmin - min;
        limit += totalmin - totalminlig;
      }
      else
      {
        limit = totalmin - totalminlig;
      }
    }
  }
  preco += limit * 0.2;
  printf("%.2f\n", preco);
  return(0);
}
