#include <stdio.h>

int main()
{
  int Y, X; scanf("%d %d", &Y, &X);
  int m[Y][X], i, j;
  for (i = 0; i < Y; i ++)
  {
    for (j = 0; j < X; j ++)
    {
      scanf("%d", &m[i][j]);
    }
  }
  int custo, melhor;
  for (j = 0; j < X; j ++)
  {
    custo = 0;
    for (i = 0; i < Y; i ++)
    {
      custo += m[i][j];
    }
    if (j == 0 || custo < melhor)
    {
      melhor = custo;
    }
  }
  printf("%d\n", melhor);
  return(0);
}
