#include <stdio.h>

int main()
{
  int i, j, x, y; scanf("%d %d", &i, &j);
  int pos = i * j, matriz[pos];
  for (x = 0; x < pos; x ++)
  {
    scanf("%d", &matriz[x]);
  }
  int aux;
  for (y = 0; y < pos; y ++)
  {
    for (x = y; x < pos; x ++)
    {
      if (matriz[x] <= matriz[y])
      {
        aux = matriz[x];
        matriz[x] = matriz[y];
        matriz[y] = aux;
      }
    }
  }
  pos = 0;
  for (y = 0; y < i; y ++)
  {
    for (x = 0; x < j - 1; x ++)
    {
      printf("%d ", matriz[pos]);
      pos ++;
    }
    printf("%d\n", matriz[pos]);
    pos ++;
  }
  return(0);
}
