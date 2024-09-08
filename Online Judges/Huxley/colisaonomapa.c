#include <stdio.h>

int main()
{
  int i, j, leri, lerj; scanf("%d\n%d", &i, &j);
  int matriz[i + 10][j + 10];
  for (lerj = 0; lerj < j; lerj ++)
  {
    for (leri = 0; leri < i; leri ++)
    {
      scanf("%d", &matriz[i][j]);
    }
  }
  int movimentos, lermove; scanf("%d", &movimentos);
  char move[movimentos + 10];
  for (lermove = 0; lermove < movimentos; lermove ++)
  {
    getchar();
    scanf("%c", &move[lermove]);
  }
  int x, y;
  scanf("%d\n%d", &x, &y);
  for (lermove = 0; lermove < movimentos; lermove ++)
  {
    if (move[lermove] == 'D')
    {
      if (matriz[x + 1][y] != 0)
      {
        x ++;
      }
    }
    if (move[lermove] == 'E')
    {
      if (matriz[x - 1][y] != 0)
      {
        x --;
      }
    }
    if (move[lermove] == 'C')
    {
      if (matriz[x][y + 1] != 0)
      {
        y ++;
      }
    }
    if (move[lermove] == 'B')
    {
      if (matriz[x][y - 1] != 0)
      {
        y --;
      }
    }
  }
  printf("(%d,%d)\n", y, x);
  return(0);
}
