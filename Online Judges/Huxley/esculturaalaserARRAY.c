#include <stdio.h>
#include <stdlib.h>

int ativ, m[11111], i, j, max, min;

int main()
{
  int altura, largura;
  while (scanf("%d %d", &altura, &largura) && !(altura == 0 && largura == 0))
  {
    max = 0, min = 11111;
    for (j = 0; j < largura; j ++)
    {
      scanf("%d", &m[j]);
      if (m[j] > max)
      {
        max = m[j];
      }
      if (m[j] < min)
      {
        min = m[j];
      }
    }
    ativ = altura - max;
    for (i = max; i >= min; i --)
    {
      for (j = 0; j < largura; j ++)
      {
        if (m[j] < i)
        {
          ativ ++;
        }
        while (m[j] < i && j < largura)
        {
          j ++;
        }
      }
    }
    printf("%d\n", ativ);
  }
  return(0);
}
