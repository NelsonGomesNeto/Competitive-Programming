#include <stdio.h>

int main()
{
  int mes, ano, bissexto = 0;
  scanf("%d %d", &mes, &ano);
  if ((ano % 4 == 0 && ano % 100 != 0))// || ano % 400)
  {
    bissexto = 1;
  }
  if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
  {
    printf("31\n");
  }
  else
  {
    if (mes == 2)
    {
      if (bissexto == 0)
      {
        printf("28\n");
      }
      else
      {
        printf("29\n");
      }
    }
    else
    {
      printf("30\n");
    }
  }
  return(0);
}
