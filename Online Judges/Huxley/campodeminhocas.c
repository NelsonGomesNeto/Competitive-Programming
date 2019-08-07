#include <stdio.h>

int main()
{
  int altura, largura; scanf("%d %d", &altura, &largura);
  int i, j, minhoca, coluna[altura], linha[largura], best = 0;
  for (i = 0; i < altura; i ++)
  {
    coluna[i] = 0;
    for (j = 0; j < largura; j ++)
    {
      if (i == 0)
        linha[j] = 0;

      scanf("%d", &minhoca);
      linha[j] += minhoca;
      if (linha[j] > best)
        best = linha[j];
      coluna[i] += minhoca;
    }
    if (coluna[i] > best)
      best = coluna[i];
  }

  /*for (i = 0; i < altura; i ++)
    if (coluna[i] > best)
      best = coluna[i];

  for (j = 0; j < largura; j ++)
    if (linha[j] > best)
      best = linha[j];*/

  printf("%d\n", best);
  return(0);
}
