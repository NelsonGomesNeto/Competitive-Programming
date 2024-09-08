#include <stdio.h>

int main()
{
  double array[30]; int ler;
  for (ler = 0; ler < 30; ler ++)
  {
    printf("Digite um numero:\n");
    scanf("%lf", &array[ler]);
  }
  for (ler = 0; ler < 30; ler ++)
  {
    if (ler % 2 != 0)
    {
      if (array[ler] - (int) array[ler] == 0)
      {
        printf("%.1lf\n", array[ler]);
      }
      else
      {
        printf("%.2lf\n", array[ler]);
      }
    }
  }
  return(0);
}
