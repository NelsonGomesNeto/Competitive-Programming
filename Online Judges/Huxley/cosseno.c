#include <stdio.h>
#include <math.h>

double pi = 3.14;

double pot(double x, int expo)
{
  double res;
  if (expo == 0)
  {
    return(1);
  }
  res = pot(x, expo / 2);
  if (expo % 2 != 0)
  {
    return (x * res * res);
  }
  return (res * res);
}

double fat(double num)
{
  if (num <= 1)
  {
    return(1);
  }
  num *= fat(num - 1);
  return(num);
}

double seno(double angulo)
{
  int i, j; double res = 0;
  for (i = 1, j = 1; i < 100; i += 2, j ++)
  {
    if (j & 1) //Impar
    {
      res += (pot(angulo, i) / fat(i));
    }
    else //Par
    {
      res -= (pot(angulo, i) / fat(i));
    }
  }
  return(res);
}

double abS(double num)
{
  return(num < 0 ? num * (-1) : num);
}

void printFormatado(double cosseno)
{
  int coss = abS(cosseno) * 1000;
  if (1000 % coss <= 1)
  {
    printf("%.1lf\n", cosseno);
  }
  else
  {
    printf("%.2lf\n", cosseno);
  }
}

int radToDeg(double ang)
{
  return((ang / pi) * 180);
}

int main()
{
  double angulo; scanf("%lf", &angulo);
  double cosseno = sqrt(1 - pot(seno(angulo), 2));
  angulo = radToDeg(angulo) % 360;
  if ((angulo >= 90 && angulo <= 270)
  ||  (angulo >= -270 && angulo <= -90))
  {
    cosseno *= -1;
  }
  printf("%.2lf\n", cosseno);
  return(0);
}
