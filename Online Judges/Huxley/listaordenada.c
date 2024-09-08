#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int ler, lista[tam];
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &lista[ler]);
  }
  int o, b, aux;
  for (o = 0; o < tam; o ++)
  {
    for (b = o; b < tam; b ++)
    {
      if (lista[b] < lista[o])
      {
        aux = lista[b];
        lista[b] = lista[o];
        lista[o] = aux;
      }
    }
  }
  for (ler = 0; ler < tam; ler ++)
  {
    printf("%d\n", lista[ler]);
  }
  return(0);
}
