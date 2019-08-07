#include <stdio.h>

int MDC(int n1, int n2)
{
  if (n1 % n2 == 0)
  {
    return(n2);
  }
  MDC(n2, n1 % n2);
}

int main()
{
  int tam; scanf("%d", &tam);
  double nume, tempo = 0; int ler, aux, bubble, ordem, num[tam], mmc;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%lf", &nume);
    num[ler] = 10 * nume;
  }
  for (ordem = 0; ordem < tam; ordem ++)
  {
    for (bubble = ordem; bubble < tam; bubble ++)
    {
      if (num[ordem] > num[bubble])
      {
        aux = num[ordem];
        num[ordem] = num[bubble];
        num[bubble] = aux;
      }
    }
  }
  while (num[0] != num[tam - 1])
  {
    mmc = num[0];
    for (ler = 0; ler < tam - 1; ler ++)
    {
      mmc = (mmc * num[ler + 1]) / MDC(num[ler],num[ler + 1]);
      num[ler] = num[tam - 1];
    }
  }
  printf("O tempo para o alinhamento dos planetas e %.1f minutos\n", (float) mmc / 10);
  return(0);
}
