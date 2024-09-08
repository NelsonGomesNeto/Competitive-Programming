#include <stdio.h>

void divisores(int numero, int divi)
{
  if (numero % divi == 0)
  {
    printf("%d\n", divi);
  }
  if (divi != 1)
  {
    divisores(numero,divi - 1);
  }
}

int main()
{
  int num; scanf("%d", &num);
  divisores(num, num);
  return(0);
}
