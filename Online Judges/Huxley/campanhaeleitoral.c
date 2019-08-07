#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char candidato[99];
  while (scanf("%s", candidato) && strcmp(candidato, "FIM") != 0)
  {
    int midias; scanf("%d", &midias);
    char midia[99]; double preco = 0;
    while (midias > 0)
    {
      getchar();
      scanf("%s", midia);
      if (strcmp(midia, "internet") == 0)
        preco += 3000;
      else if (strcmp(midia, "revista") == 0)
        preco += 750;
      else if (strcmp(midia, "outdoor") == 0)
        preco += 1500;
      else if (strcmp(midia, "radio") == 0)
      {
        getchar();
        scanf("%s", midia);
        if (strcmp(midia, "fm") == 0)
          preco += 500;
        else
          preco += 300;
      }
      else
      {
        int horario; scanf("%d", &horario);
        if (horario <= 20)
          preco += 1200;
        else
          preco += 2000;
      }
      midias --;
    }
    printf("%s: %.2lf\n", candidato, preco);
  }
  return(0);
}
