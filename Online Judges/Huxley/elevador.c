#include <stdio.h>

int main()
{
  int Nleituras, Capacidade, pout, pin, pessoas = 0;
  int excedeu = 0;
  scanf("%i %i", &Nleituras, &Capacidade);
  while (Nleituras > 0)
  {
    scanf("%i %i", &pout, &pin);
    pessoas += pin - pout;
    if (pessoas > Capacidade)
    {
      excedeu ++;
    }
    Nleituras --;
  }
  if (excedeu > 0)
  {
    printf("S\n");
  }
  else
  {
    printf("N\n");
  }
  return(0);
}
