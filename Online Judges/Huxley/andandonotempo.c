#include <stdio.h>

int main()
{
  int tempo[3];
  scanf("%d %d %d", &tempo[0], &tempo[1], &tempo[2]);
  int i, j, all, atual;
  for (i = 0; i < 3; i ++)
  {
    atual = 0;
    for (j = i, all = 0; all < 3; all ++, j ++)
    {
      if (j >= 3)
      {
        j = 0;
      }
      if (tempo[j] == atual)
      {
        printf("S\n");
        return(0);
      }
      atual += tempo[j];
    }
  }
  printf("N\n");
  return(0);
}
