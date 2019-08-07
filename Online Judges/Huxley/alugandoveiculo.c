#include <stdio.h>

int main()
{
  int dias, Km;
  float pago = 0;
  scanf("%i\n%i", &dias, &Km);
  if (Km / dias >= 100)
  {
    pago = ((Km - (100 * dias)) * 12);
  }
  pago += (90 * dias);
  printf("%.2f\n", pago);
  return(0);
}
