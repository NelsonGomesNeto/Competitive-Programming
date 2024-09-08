#include <stdio.h>

int main()
{
  long long int n, m, i, j, diagX = 0, diagxY, diagyY;
  double resultado, soma = 1, t = 0, a = 0, b = 0, c = 0, d = 0, x = 0, y = 0;
  //unsigned long long int matriz[1000][1000];
  while (scanf("%Ld%Ld", &n, &m) && !(n <= 0 && m <= 0))
  {
    resultado = 0;
    if (m > 0 && n > 0)
    {
      diagyY = (m - n); diagxY = (n - m);
      if (diagyY < 0)
      {
        diagyY = 0;
      }
      if (diagxY < 0)
      {
        diagxY = 0;
      }
      soma = 1, diagX = 0, t = 0, a = 0, b = 0, c = 0, d = 0, x = 0, y = 0;
      for (j = 0; j < n; j ++)
      {
        for (i = 0; i < m; i ++)
        {
          t += soma;
          //matriz[i][j] = soma;
          soma ++;
          if (i == 0)
          {
            //a += matriz[i][j];
            a += soma - 1;
          }
          if (i == m - 1)
          {
            //b += matriz[i][j];
            b += soma - 1;
          }
          if (j == 0)
          {
            //c += matriz[i][j];
            c += soma - 1;
          }
          if (j == n - 1)
          {
            //d += matriz[i][j];
            d += soma - 1;
          }
          if (i == diagX && j == diagX)
          {
            //printf("X: %d ~ %d %d\n", matriz[i][j], i, j);
            //x += matriz[i][j];
            x += soma - 1;
            diagX ++;
          }
          if (i == diagyY && j == diagxY)
          {
            //printf("Y: %Ld ~ %Ld %Ld\n", matriz[i][j], i, j);
            //y += matriz[i][j];
            y += soma - 1;
            diagyY ++; diagxY ++;
          }
        }
      }
      /*for (j = n - 1; j >= 0; j --)
      {
        for (i = m - 1; i >= 0; i --)
        {
          if (i == diagxY && j == diagyY)
          {
            //printf("Y: %Ld ~ %d %d\n", matriz[i][j], i, j);
            y += matriz[i][j];
            diagyY --; diagxY --;
          }
        }
      }*/
      if (n * m != 0 && (double) (double)(t - (x + y) + ((double)a * b) - ((double)c * d)) != 0)
      {
        resultado = (double) ((double)(t - (x + y) + ((double)a * b) - ((double)c * d)) / ((double)n * m));
      }
    }
    printf("%.2f\n", resultado);
  }
  return(0);
}
