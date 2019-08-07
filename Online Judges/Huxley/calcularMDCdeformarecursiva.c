#include <stdio.h>

int once = 0, divi;

int mdc(int numero1, int numero2)
{
  if (once == 0)
  {
    divi = numero2;
    once ++;
  }
  if (numero1 % divi != 0 || numero2 % divi != 0)
  {
    divi --; mdc(numero1, numero2);
  }
  else
  {
    return(divi);
  }
}

int main()
{
  int num1, num2, aux, max;
  scanf("%d\n%d", &num1, &num2);
  if (num2 > num1)
  {
    aux = num1;
    num1 = num2;
    num2 = aux;
  }
  max = mdc(num1, num2);
  printf("%d\n", max);
  return(0);
}
