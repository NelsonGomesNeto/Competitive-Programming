#include <stdio.h>

int main()
{
  int x, y; scanf("%d %d", &y, &x);
  int matriz[y + 2][x + 2], i, j, iR, jR, land, costa = 0;
  char terra;
  for (j = 0; j < y + 2; j ++)
  {
    for (i = 0; i < x + 2; i ++)
    {
      matriz[j][i] = 0;
    }
  }
  getchar();
  for (j = 1; j < y + 1; j ++)
  {
    for (i = 1; i < x + 1; i ++)
    {
      scanf("%c", &terra);
      matriz[j][i] = terra == '#' ? 1 : 0;
    }
    scanf("%c", &terra); //Lendo o '\n'
  }
  //printf("~~~~~~~~\n");
  for (j = 1; j < y + 1; j ++)
  {
    for (i = 1; i < x + 1; i ++)
    {
      land = 0;
      //printf("%d ", matriz[j][i]);
      if (matriz[j][i] == 1)
      {
        if (matriz[j][i - 1] == 1 && matriz[j][i + 1] == 1)
        {
          if (matriz[j - 1][i] == 1 && matriz[j + 1][i] == 1)
          {
            land = 1;
          }
        }
      }
      if (land != 1 && matriz[j][i] == 1)
      {
        costa ++;
      }
    }
    //printf("\n");
  }
  printf("%d\n", costa);
  return(0);
}
