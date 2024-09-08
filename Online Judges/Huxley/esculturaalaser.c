#include <stdio.h>
#include <stdlib.h>


int main()
{
  int altura, largura;
  while (scanf("%d%d", &altura, &largura) && !(altura == 0 && largura == 0))
  {
    int i, bloco, ativ = 0, prev = altura;
    for (i = 0; i < largura; i ++)
    {
      scanf("%d", &bloco);
      if (bloco < prev)
      {
        ativ += (prev - bloco);
      }
      prev = bloco;
    }
    printf("%d\n", ativ);
  }
  return(0);
}
