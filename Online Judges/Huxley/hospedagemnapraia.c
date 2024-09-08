#include <stdio.h>
#include <string.h>

int main()
{
  char tipo[99]; float preco = 0;
  int dias = 0, convert;
  scanf("%[^\n]s", &*tipo);
  for (convert = 0; convert < 99; convert ++)
  {
    tipo[convert] = tolower(tipo[convert]);
  }
  scanf("%i", &dias);
  if (strcmp(tipo,"individual") == 0)
  {
    preco = 125 * dias;
  }
  else if (strcmp(tipo,"suite dupla") == 0 || strcmp(tipo,"suíte dupla") == 0)
  {
    preco = 140 * dias;
  }
  else
  {
    preco = 180 * dias;
  }
  if (dias >= 3)
  {
    preco *= 0.85;
  }
  printf("%.2f\n", preco);
  return(0);
}
