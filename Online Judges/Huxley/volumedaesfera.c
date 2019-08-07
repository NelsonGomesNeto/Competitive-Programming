#include <stdio.h>
#include <math.h>

int main()
{
  double raio, volume, pi = 3.1416;
  while (scanf("%lf", &raio) != EOF)
  {
    volume = (4 * pi * raio * raio * raio) / 3;
    printf("%.2lf\n", volume);
  }
  return(0);
}
