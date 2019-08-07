#include <stdio.h>

int main()
{
  int x, y, field = 1;
  while (scanf("%d %d", &y, &x) && !(y == 0 && x == 0))
  {
    if (field > 1)
    {
      printf("\n");
    }
    char matriz[y + 2][x + 2], bomba; int i, j, iR, jR, costa = 0;
    char campo;
    for (j = 0; j < y + 2; j ++)
    {
      for (i = 0; i < x + 2; i ++)
      {
        matriz[j][i] = '.';
      }
    }
    getchar();
    for (j = 1; j < y + 1; j ++)
    {
      for (i = 1; i < x + 1; i ++)
      {
        scanf("%c", &campo);
        matriz[j][i] = campo;
      }
      scanf("%c", &campo); //Lendo o '\n'
    }
    for (j = 1; j < y + 1; j ++)
    {
      for (i = 1; i < x + 1; i ++)
      {
        bomba = '0';
        if (matriz[j][i] == '.')
        {
          for (jR = j - 1; jR < j + 2; jR ++)
          {
            for (iR = i - 1; iR < i + 2; iR ++)
            {
              if (matriz[jR][iR] == '*' && !(jR == j && iR == i))
              {
                bomba ++;
              }
            }
          }
          matriz[j][i] = bomba;
        }
      }
    }
    printf("Field #%d:\n", field);
    field ++;
    for (j = 1; j < y + 1; j ++)
    {
      for (i = 1; i < x + 1; i ++)
      {
        printf("%c", matriz[j][i]);
      }
      printf("\n");
    }
  }
  return(0);
}
