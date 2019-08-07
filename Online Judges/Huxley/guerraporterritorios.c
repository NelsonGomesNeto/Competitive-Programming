#include <stdio.h>

int main()
{
  int regioes, ler, media = 0, soma = 0; scanf("%d", &regioes);
  int tamanho[regioes];
  for (ler = 0; ler < regioes; ler ++)
  {
    scanf("%d", &tamanho[ler]);
    media += tamanho[ler];
  }
  media /= 2;
  ler = 0;
  while (soma < media)
  {
    soma += tamanho[ler];
    ler ++;
  }
  printf("%d\n", ler);
  return(0);
}
