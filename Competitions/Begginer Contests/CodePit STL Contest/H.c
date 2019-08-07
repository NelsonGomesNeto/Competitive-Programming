#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  long long int tam, num;
  while (scanf("%Ld %Ld", &tam, &num) && !(tam == 0 && num == 0))
  {
    //printf("PDundim\n");
    long long int j, i, limitY = 1, limitX = 1, y = 0, x = 0; long double cont = 1, pot = 1;
    i = (tam - 1) / 2; j = (tam - 1) / 2;
    y = 0; x = 0;
    long long int jM = 1, iM = -1;
    while (cont < num)
    {
      pot += 2;
      cont = pow(pot,2);
      i ++; j ++;
      limitY += 2; limitX += 2;
    }
    if (pot > 1)
    {
      cont = pow(pot - 2,2);
      i --; j --;
      limitY -= 2; limitX -= 2;
    }
    //printf("%Lf ~%Ldx%Ld\n", cont, limitY, limitX);
    y = limitY - 1;
    while (cont <= num)
    {
      while (y < limitY && cont <= num)
      {
        if (cont == num)
        {
          cont = (tam * tam) + 1;
          printf("Line = %Ld, column = %Ld.\n", j + 1, i + 1);
          break;
        }
        cont ++;
        j += jM;
        y ++;
      }
      y = 0;
      limitY ++;
      jM *= -1;
      while (x < limitX && cont <= num)
      {
        if (cont == num)
        {
          cont = (tam * tam) + 1;
          printf("Line = %Ld, column = %Ld.\n", j + 1, i + 1);
          break;
        }
        cont ++;
        i += iM;
        x ++;
      }
      x = 0;
      limitX ++;
      iM *= -1;
    }
    /*for (j = 0; j < tam; j ++)
    {
      for (i = 0; i < tam; i ++)
      {
          printf("%Ld ", m[j][i]);
      }
      printf("\n");
    }
    for (j = 0; j < tam; j ++)
    {
      for (i = 0; i < tam; i ++)
      {
        if (m[j][i] == num)
        {
          printf("Line = %d, column = %d.\n", j + 1, i + 1);
        }
      }
    }*/
  }
  return(0);
}
