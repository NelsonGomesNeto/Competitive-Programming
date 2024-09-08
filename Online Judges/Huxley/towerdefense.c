#include <stdio.h>

int main()
{
  int Y, X; scanf("%d %d", &Y, &X);
  char jogo[Y + 2][X + 2]; int j, i;

  for (j = 0; j <= Y + 1; j ++)
  {
    for (i = 0; i <= X + 1; i ++)
    {
      jogo[j][i] = '.';
    }
  }

  for (j = 1; j <= Y; j ++)
  {
    getchar();
    for (i = 1; i <= X; i ++)
    {
      scanf("%c", &jogo[j][i]);
    }
  }
  for (j = 1; j <= Y; j ++)
  {
    for (i = 1; i <= X; i ++)
    {
      if (jogo[j][i] == '&')
      {
        int jM, iM;
        for (jM = j - 1; jM <= j + 1; jM ++)
        {
          for (iM = i - 1; iM <= i + 1; iM ++)
          {
            if (jogo[jM][iM] == '*' && !(jM == j && iM == i))
            {
              jogo[jM][iM] = '.';
            }
          }
        }
      }
    }
  }
  for (j = 1; j <= Y; j ++)
  {
    for (i = 1; i <= X; i ++)
    {
      if (jogo[j][i] == '*')
      {
        printf("N\n");
        return(0);
      }
    }
  }
  printf("S\n");
  return(0);
}
