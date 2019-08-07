#include <stdio.h>

int main()
{
  int pago, comida, bonus;
  scanf("%i\n%i", &comida, &pago);
  if (pago < 3.25)
  {
    pago += pago;
  }
  pago = pago * 100 * comida;
  bonus = (pago - (comida * 325)) / 325;
  printf("%i\n", bonus);
  return(0);
}
