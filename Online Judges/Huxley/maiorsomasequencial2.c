#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int num[tam], ler, soma = 0, aux = -1000000, tostop = 0, posi = 0, loop = 0, fim = 0;
  int negativo = 0;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &num[ler]);
  }
  for (posi = 0; posi < tam; posi ++)
  {
    soma = 0; fim = 0;
    for (loop = posi; fim < tam; loop ++, fim ++)
    {
      loop = loop % tam;
      soma += num[loop];
      if (soma > aux)
      {
        aux = soma;
      }
    }
  }
  printf("%d\n", aux);
  return(0);
}
