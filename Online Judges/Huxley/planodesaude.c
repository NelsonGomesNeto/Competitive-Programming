#include <stdio.h>
#include <string.h>

int main()
{
  char tipo[10]; float preco, total = 0;
  int repeat, convert, exame = 2, consulta = 3;
  for (repeat = 0; repeat < 8; repeat ++)
  {
    scanf("%s", &*tipo);
    for (convert = 0; convert < 10; convert ++)
    {
      tipo[convert] = tolower(tipo[convert]);
    }
    scanf("%f", &preco);
    if (strcmp(tipo,"exame") == 0)
    {
      if (exame <= 0)
      {
        total += preco * 0.6;
      }
      exame --;
    }
    else
    {
      if (consulta <= 0)
      {
        total += preco * 0.3;
      }
      consulta --;
    }
  }
  printf("%.2f\n", total);
}
