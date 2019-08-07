#include <stdio.h>
#include <string.h>

int main()
{
  char tipo[99];
  int bolas, convert = 0;
  float pago;
  scanf("%[^\n]s", &*tipo);
  scanf("%i", &bolas);
  while (convert <= 99)
  {
    tipo[convert] = tolower(tipo[convert]);
    convert ++;
  }
  if (strcmp(tipo,"morango") == 0 || strcmp(tipo,"cereja") == 0)
  {
    pago = 4.5 * bolas;
  }
  else if (strcmp(tipo,"damasco") == 0 || strcmp(tipo,"siriguela") == 0)
  {
    pago = 3.8 * bolas;
  }
  else
  {
    pago = 2.75 * bolas;
  }
  if (bolas > 2)
  {
    printf("%.2f\nCOM CALDA\n", pago);
  }
  else
  {
    printf("%.2f\nSEM CALDA\n", pago);
  }
  return(0);
}
