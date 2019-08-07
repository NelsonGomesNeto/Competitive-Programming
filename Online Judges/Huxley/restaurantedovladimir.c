#include <stdio.h>
#include <string.h>

int main()
{
  char tipo[99], sabor[99];
  int quantidade, convert = 0;
  float preco = 0;
  scanf("%s\n%s\n%i", &*tipo, &*sabor, &quantidade);
  while (convert <= 99)
  {
    tipo[convert] = tolower(tipo[convert]);
    convert ++;
  }
  convert = 0;
  while (convert <= 99)
  {
    sabor[convert] = tolower(sabor[convert]);
    convert ++;
  }
  if (strcmp(tipo,"pizza") == 0)
  {
    if (strcmp(sabor,"calabresa") == 0 || strcmp(sabor,"marguerita") == 0)
    {
      preco += (20.6 * quantidade) + (quantidade * 2);
    }
    else
    {
      preco += (30.9 * quantidade) + (quantidade * 2);
    }
  }
  else
  {
    if (strcmp(sabor,"queijo") == 0)
    {
      preco += (18 * quantidade) + (quantidade * 2);;
    }
    else
    {
      preco += (23 * quantidade) + (quantidade * 2);;
    }
  }
  printf("%.2f\n", preco);
  return(0);
}
