#include <stdio.h>

int main()
{
  int mes;
  scanf("%i", &mes);
  if (mes < 1 || mes > 12)
  {
    printf("invalido\n");
  }
  else if (mes == 1)
  {
    printf("janeiro\n");
  }
  else if (mes == 2)
  {
    printf("fevereiro\n");
  }
  else if (mes == 3)
  {
    printf("marco\n");
  }
  else if (mes == 4)
  {
    printf("abril\n");
  }
  else if (mes == 5)
  {
    printf("maio\n");
  }
  else if (mes == 6)
  {
    printf("junho\n");
  }
  else if (mes == 7)
  {
    printf("julho\n");
  }
  else if (mes == 8)
  {
    printf("agosto\n");
  }
  else if (mes == 9)
  {
    printf("setembro\n");
  }
  else if (mes == 10)
  {
    printf("outubro\n");
  }
  else if (mes == 11)
  {
    printf("novembro\n");
  }
  else if (mes == 12)
  {
    printf("dezembro\n");
  }
  return(0);
}
