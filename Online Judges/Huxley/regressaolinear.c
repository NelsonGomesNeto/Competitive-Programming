#include <stdio.h>
#include <math.h>

int main()
{
  int n;
  while (scanf("%d", &n) && n != 0)
  {
    float x[n], y[n]; int ler;
    float a, b, R, somaXY = 0, somaX = 0, somaY = 0, somaX2 = 0, somaY2 = 0;
    for (ler = 0; ler < n; ler ++)
    {
      scanf("%f %f", &x[ler], &y[ler]);
      somaX += x[ler]; somaX2 += pow(x[ler],2);
      somaY += y[ler]; somaY2 += pow(y[ler],2);
      somaXY += (x[ler] * y[ler]);
    }
    a = ((n * somaXY) - (somaX * somaY)) / ((n * somaX2) - pow(somaX,2));
    b = ((somaY * somaX2) - (somaX * somaXY)) / ((n * somaX2) - pow(somaX,2));
    R = ((n * somaXY) - (somaX * somaY)) / (sqrt((n * somaX2) - pow(somaX,2)) * sqrt((n * somaY2) - pow(somaY,2)));
    printf("a = %.2f, b = %.2f, R = %.2f\n", a, b, R);
  }
  return(0);
}
