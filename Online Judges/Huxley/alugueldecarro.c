#include <stdio.h>
#include <math.h>

void printFormated(double num)
{
  if (((int) (num * 100)) % 10 == 0)
    printf("%.1f\n", num);
  else
    printf("%.2f\n", num);
}

int main()
{
  int dias, kilometros; scanf("%d\n%d", &dias, &kilometros);

  printFormated((dias * 30 + kilometros * 0.01) * 0.9);

  return(0);
}
