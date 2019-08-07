#include <stdio.h>

int main()
{
  int regioes, ler, linha; scanf("%d", &regioes);
  int mapa[regioes][regioes], chuva[regioes][regioes];
  for (ler = 0; ler < regioes; ler ++)
  {
    for (linha = 0; linha < regioes; linha ++)
    {
      scanf("%d", &mapa[ler][linha]);
    }
  }
  for (ler = 0; ler < regioes; ler ++)
  {
    for (linha = 0; linha < regioes; linha ++)
    {
      scanf("%d", &chuva[ler][linha]);
    }
  }
  for (ler = 0; ler < regioes; ler ++)
  {
    for (linha = 0; linha < regioes; linha ++)
    {
      printf("%d ", mapa[ler][linha] + chuva[ler][linha]);
    }
    printf("\n");
  }
  return(0);
}
