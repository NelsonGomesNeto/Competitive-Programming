#include <stdio.h>

int main()
{
  int digitos, ler = 0, aux, ordem; scanf("%d", &digitos);
  int num[digitos], dec[digitos];
  for (ler = 0; ler < digitos; ler ++)
  {
    scanf("%d", &num[ler]);
    dec[ler] = num[ler];
  }
  for (ler = digitos - 1; ler > 0; ler --) //Printa na ordem inversa
  {
    printf("%d ", num[ler]);
  }
  printf("%d\n", num[ler]);

  aux = num[0];
  for (ler = 0; ler < digitos - 1; ler ++) //Desloca para esquerda
  {
    num[ler] = num[ler + 1];
  }
  num[ler] = aux;
  for (ler = 0; ler < digitos - 1; ler ++) //Printa deslocado
  {
    printf("%d ", num[ler]);
  }
  printf("%d\n", num[ler]);

  for (ler = 0; ler < digitos; ler ++) //Deixa em ordem decresente
  {
    for (ordem = ler; ordem < digitos; ordem ++)
    {
      if (dec[ler] < dec[ordem])
      {
        aux = dec[ler];
        dec[ler] = dec[ordem];
        dec[ordem] = aux;
      }
    }
  }
  for (ler = 0; ler < digitos - 1; ler ++) //Printa em ordem decrescente
  {
    printf("%d ", dec[ler]);
  }
  printf("%d\n", dec[ler]);
  return(0);
}
