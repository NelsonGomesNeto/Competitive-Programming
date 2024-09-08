#include <stdio.h>
#include <string.h>

int main()
{
  int L, C; scanf("%d %d", &L, &C);
  int cadeira[L + 999][C + 999], i, j, iM, jM, final[L + 999][C + 999], cad = 1, move = 0, change, aux;
  char moveCHAR[1010]; int X[1010], Y[1010];
  for (j = 0; j < L; j ++)
  {
    for (i = 0; i < C; i ++)
    {
      scanf("%d", &cadeira[j][i]);
      final[j][i] = cad;
      cad ++;
    }
  }
  for (j = 0; j < L; j ++)
  {
    for (i = 0; i < C; i ++)
    {
      for (jM = 0; jM < L; jM ++)
      {
        for (iM = 0; iM < C; iM ++)
        {
          if (final[jM][iM] == cadeira[j][i])
          {
            if (j != jM)
            {
              moveCHAR[move] = 'L'; X[move] = jM + 1; Y[move] = j + 1;
              move ++;
              for (change = 0; change < C; change ++)
              {
                aux = cadeira[j][change];
                cadeira[j][change] = cadeira[jM][change];
                cadeira[jM][change] = aux;
              }
              i = 0; iM = 0; j = 0; jM = 0;
            }
          }
        }
      }
    }
  }
  for (j = 0; j < L; j ++)
  {
    for (i = 0; i < C; i ++)
    {
      for (jM = 0; jM < L; jM ++)
      {
        for (iM = 0; iM < C; iM ++)
        {
          if (final[jM][iM] == cadeira[j][i])
          {
            if (i != iM)
            {
              moveCHAR[move] = 'C'; X[move] = iM + 1; Y[move] = i + 1;
              move ++;
              for (change = 0; change < L; change ++)
              {
                aux = cadeira[change][i];
                cadeira[change][i] = cadeira[change][iM];
                cadeira[change][iM] = aux;
              }
              i = 0; iM = 0; j = 0; jM = 0;
            }
          }
        }
      }
    }
  }
  printf("%d\n", move);
  for (i = 0; i < move; i ++)
  {
    printf("%c %d %d\n", moveCHAR[i], X[i], Y[i]);
  }
  return(0);
}
