#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  float num[tam], aux[tam], auxSort; int ler, bubble, ordem, divi, tempo = 1;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%f", &num[ler]);
    aux[ler] = num[ler];
  }
  for (ordem = 0; ordem < tam; ordem ++)
  {
    for (bubble = ordem; bubble < tam; bubble ++)
    {
      if (num[ordem] > num[bubble])
      {
        auxSort = num[ordem];
        num[ordem] = num[bubble];
        num[bubble] = auxSort;

        auxSort = aux[ordem];
        aux[ordem] = aux[bubble];
        aux[bubble] = auxSort;
      }
    }
  }
  while (num[0] != num[tam - 1])
  {
    for (ler = 0; ler < tam; ler ++)
    {
      divi = 2;
      if (num[ler] != 1)
      {
        while ((int) num[ler] % divi != 0)
        {
          divi ++;
        }
        num[ler] /= divi;
      }
      tempo *= divi;
    }
  }
  printf("O tempo para o alinhamento dos planetas e %d.0 minutos\n", tempo);
  return(0);
}
