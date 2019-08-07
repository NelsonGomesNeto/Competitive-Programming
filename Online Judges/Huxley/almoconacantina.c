#include <stdio.h>
#include <string.h>

int main()
{
  char comida[99], bebida[99];
  int convert = 0;
  float pago = 0;
  scanf("%s\n%s", &*comida, &*bebida);
  //scanf("%[^\n]s", &*bebida);
  while (convert <= 99)
  {
    comida[convert] = tolower(comida[convert]);
    convert ++;
  }
  convert = 0;
  while (convert <= 99)
  {
    bebida[convert] = tolower(bebida[convert]);
    convert ++;
  }
  if (strcmp(comida,"lasanha") == 0)
  {
    pago += 8;
  }
  else
  {
    pago += 11;
  }
  if (strcmp(bebida,"refrigerante") == 0)
  {
    pago += 3;
  }
  else
  {
    pago += 2.50;
  }
  printf("%.2f\n", pago);
  return(0);
}
