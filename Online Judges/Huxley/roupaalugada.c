#include <stdio.h>
#include <string.h>

int main()
{
  char tipo[99], item[99];
  int convert = 0;
  float preco = 0;
  scanf("%s\n%s", &*tipo, &*item);
  while (convert <= 99)
  {
    tipo[convert] = tolower(tipo[convert]);
    convert ++;
  }
  convert = 0;
  while (convert <= 99)
  {
    item[convert] = tolower(item[convert]);
    convert ++;
  }
  if (strcmp(tipo,"terno") == 0)
  {
    if (strcmp(item,"simples") == 0)
    {
      preco += 120.40 * (0.93);
    }
    else if (strcmp(item,"completo") == 0)
    {
      preco += 150.35 * (0.93);
    }
    else
    {
      preco += 180.70 * (0.93);
    }
  }
  else
  {
    if (strcmp(item,"gravata") == 0)
    {
      preco += 30;
    }
    else if (strcmp(item,"sapato") == 0)
    {
      preco += 80;
    }
    else
    {
      preco += 15;
    }
  }
  printf("%.2f\n", preco);
  return(0);
}
