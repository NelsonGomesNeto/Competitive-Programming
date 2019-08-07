#include <stdio.h>

int main()
{
  int obj, max; scanf("%d %d", &obj, &max);
  int peso[obj], valor[obj], ler, check, Pat, Vat;
  for (ler = 0; ler < obj; ler ++)
  {
    scanf("%d", &valor[ler]);
  }
  for (ler = 0; ler < obj; ler ++)
  {
    scanf("%d", &peso[ler]);
  }
  int o, b, aux;
  for (o = 0; o < obj; o ++)
  {
    for (b = o; b < obj; b ++)
    {
      if (valor[o] < valor[b])
      {
        aux = valor[o];
        valor[o] = valor[b];
        valor[b] = aux;

        aux = peso[o];
        peso[o] = peso[b];
        peso[b] = aux;
      }
    }
  }
  int tudo, i, dinheiros = 0;
  for (check = 0; check < obj; check ++)
  {
    Pat = 0; Vat = 0;
    tudo = 0, i = check;
    while (Pat <= max && tudo < obj)
    {
      Pat += peso[i];
      Vat += valor[i];
      if (Vat > dinheiros && Pat <= max)
      {
        dinheiros = Vat;
      }
      if (Pat >= max)
      {
        Pat -= peso[i];
        Vat -= valor[i];
      }
      i ++;
      i %= obj;
      tudo ++;
      //printf("%d~%d\n", Pat, Vat);
    }
  }
  printf("%d\n", dinheiros);
  return(0);
}
