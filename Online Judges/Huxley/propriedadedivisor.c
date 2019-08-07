#include <stdio.h>

int main()
{
  int num, esquerda;
  scanf("%i", &num);
  esquerda = num / 10;
  if (num % 10 != 0 && num % esquerda == 0)
  {
    printf("SIM\n");
  }
  else
  {
    printf("NAO\n");
  }
  return(0);
}
