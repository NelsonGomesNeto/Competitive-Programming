#include <stdio.h>

int main()
{
  int y, x, auX, auY, i, j, pintados, ler, iF, jF, pintar = 1, quantos = 1;
  scanf("%d %d %d %d %d", &y, &x, &j, &i, &pintados);
  int matriz[y + 2][x + 2];
  for (jF = 0; jF < y + 2; jF ++)
  {
    for (iF = 0; iF < x + 2; iF ++)
    {
      matriz[jF][iF] = 0;
    }
  }
  for (jF = 0, iF = 0; jF < y + 2; jF ++)
  {
    matriz[jF][iF] = 1;
    matriz[jF][iF + x + 1] = 1;
  }
  for (iF = 0, jF = 0; iF < x + 2; iF ++)
  {
    matriz[jF][iF] = 1;
    matriz[jF + y + 1][iF] = 1;
  }

  matriz[j][i] = 2;
  for (ler = 0; ler < pintados; ler ++)
  {
    scanf("%d %d", &auY, &auX);
    matriz[auY][auX] = 1;
  }
  while (pintar != 0)
  {
    pintar = 0;
    for (j = 1; j < y + 1; j ++)
    {
      for (i = 1; i < x + 1; i ++)
      {
        if (matriz[j][i] == 2)
        {
          for (jF = j - 1; jF < j + 2; jF ++)
          {
            for (iF = i - 1; iF < i + 2; iF ++)
            {
              if (matriz[jF][iF] < 1)
              {
                matriz[jF][iF] = 2;
                pintar ++; quantos ++;
              }
            }
          }
        }
      }
    }
  }
  printf("%d\n", quantos);
  return(0);
}
