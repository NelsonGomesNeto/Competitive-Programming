#include <stdio.h>

int main()
{
  int tam, ler, posi, quantos, soma = 0; scanf("%d", &tam);
  int num[tam];
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &num[ler]);
  }
  scanf("%d\n%d", &posi, &quantos);
  while (quantos > 0)
  {
    if (posi >= tam)
    {
      posi %= tam;
    }
    soma += num[posi];
    posi ++;
    quantos --;
  }
  printf("%d\n", soma);
  return(0);
}
