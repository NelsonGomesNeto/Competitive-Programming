#include <stdio.h>

int main()
{
  int testes, exec, ler, CPF[12], soma = 0; scanf("%d", &testes);
  for (exec = 1; exec <= testes; exec ++)
  {
    soma = 0;
    for (ler = 0; ler < 9; ler ++)
    {
      scanf("%d", &CPF[ler]);
      soma += CPF[ler] * (11 - (ler + 1));
    }
    if (soma % 11 < 2)
    {
      CPF[9] = 0;
    }
    else
    {
      CPF[9] = 11 - (soma % 11);
    }

    soma = 0;
    for (ler = 0; ler < 10; ler ++)
    {
      soma += CPF[ler] * (12 - (ler + 1));
    }
    if (soma % 11 < 2)
    {
      CPF[10] = 0;
    }
    else
    {
      CPF[10] = 11 - (soma % 11);
    }
    printf("Caso %d: ", exec);
    for (ler = 0; ler < 11; ler ++)
    {
      printf("%d", CPF[ler]);
      if (ler == 8)
      printf("-");
    }
    printf("\n");
  }
  return(0);
}
