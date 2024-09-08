#include <stdio.h>
#include <string.h>

int main()
{
  char tipo[99];
  int anos, convert = 0;
  float pago;
  scanf("%[^\n]s", &*tipo);
  scanf("%i", &anos);
  while (convert <= 99)
  {
    tipo[convert] = tolower(tipo[convert]);
    convert ++;
  }
  if (strcmp(tipo,"mural") == 0)
  {
    pago = 200 * anos;
  }
  else if (strcmp(tipo,"o coreto") == 0)
  {
    pago = 235 * anos;
  }
  else if (strcmp(tipo,"meu lar") == 0)
  {
    pago = (180 * anos) * 0.9;
  }
  else if (strcmp(tipo,"sua mesa") == 0)
  {
    pago = (230 * anos) * 0.9;
  }
  printf("%.2f\n", pago);
  return(0);
}
