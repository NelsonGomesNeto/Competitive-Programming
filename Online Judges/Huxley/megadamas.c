#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int comeu, best, aux[3], Ymax, Xmax;
int jogo[30][30];

void play (int y, int x, int eat)
{
  /*int i, j;
  for (i = 0; i < 3; i ++)
  {
    for (j = 0; j < 3; j ++)
    {
      printf("%d ", jogo[i][j]);
    } printf("\n");
  }*/
  if (eat > comeu)
  {
    comeu = eat;
  }
  if ((y + 1 < Ymax && x + 1 < Xmax) && jogo[y + 1][x + 1] == 2 && (y + 2 < Ymax && x + 2 < Xmax) && jogo[y + 2][x + 2] == 0)
  {
    aux[0] = jogo[y][x]; jogo[y][x] = 0;
    aux[1] = jogo[y + 1][x + 1]; jogo[y + 1][x + 1] = 0;
    aux[2] = jogo[y + 2][x + 2]; jogo[y + 2][x + 2] = 1;
    play (y + 2, x + 2, eat + 1);
    jogo[y][x] = aux[0];
    jogo[y + 1][x + 1] = aux[1];
    jogo[y + 2][x + 2] = aux[2];
  }
  if ((y - 1 >= 0 && x + 1 < Xmax) && jogo[y - 1][x + 1] == 2 && (y - 2 >= 0 && x + 2 < Xmax) && jogo[y - 2][x + 2] == 0)
  {
    aux[0] = jogo[y][x]; jogo[y][x] = 0;
    aux[1] = jogo[y - 1][x + 1]; jogo[y - 1][x + 1] = 0;
    aux[2] = jogo[y - 2][x + 2]; jogo[y - 2][x + 2] = 1;
    play (y - 2, x + 2, eat + 1);
    jogo[y][x] = aux[0];
    jogo[y - 1][x + 1] = aux[1];
    jogo[y - 2][x + 2] = aux[2];
  }
  if ((y + 1 < Ymax && x - 1 >= 0) && jogo[y + 1][x - 1] == 2 && (y + 2 < Ymax && x - 2 >= 0) && jogo[y + 2][x - 2] == 0)
  {
    aux[0] = jogo[y][x]; jogo[y][x] = 0;
    aux[1] = jogo[y + 1][x - 1]; jogo[y + 1][x - 1] = 0;
    aux[2] = jogo[y + 2][x - 2]; jogo[y + 2][x - 2] = 1;
    play (y + 2, x - 2, eat + 1);
    jogo[y][x] = aux[0];
    jogo[y + 1][x - 1] = aux[1];
    jogo[y + 2][x - 2] = aux[2];
  }
  if ((y - 1 >= 0 && x - 1 >= 0) && jogo[y - 1][x - 1] == 2 && (y - 2 >= 0 && x - 2 >= 0) && jogo[y - 2][x - 2] == 0)
  {
    aux[0] = jogo[y][x]; jogo[y][x] = 0;
    aux[1] = jogo[y - 1][x - 1]; jogo[y - 1][x - 1] = 0;
    aux[2] = jogo[y - 2][x - 2]; jogo[y - 2][x - 2] = 1;
    play (y - 2, x - 2, eat + 1);
    jogo[y][x] = aux[0];
    jogo[y - 1][x - 1] = aux[1];
    jogo[y - 2][x - 2] = aux[2];
  }
}

int main()
{
  int lin, col;
  while (scanf("%d %d", &lin, &col) && !(lin == 0 && col == 0))
  {
    int ler, i, j, alternate = 0;
    int fim = (int) ceil((float)(lin * col) / 2);
    for (i = 0; i < lin; i ++)
    {
      for (j = 0; j < col; j ++)
      {
        jogo[i][j] = 3;
      }
    }
    i = lin - 1; j = 0;
    for (ler = 0; ler < fim; ler ++)
    {
      int num;
      scanf("%d", &num);
      jogo[i][j] = num;
      j += 2;
      if (j >= col)
      {
        if (alternate == 0)
        {
          j = 1;
          alternate --;
        }
        else
        {
          j = 0;
          alternate ++;
        }
        i --;
      }
    }
    Ymax = lin;
    Xmax = col;
    comeu = 0;
    for (i = 0; i < lin; i ++)
    {
      for (j = 0; j < col; j ++)
      {
        //printf("%d ", jogo[i][j]);
        if (jogo[i][j] == 1)
        {
          play(i, j, 0);
        }
      } //printf("\n");
    }
    printf("%d\n", comeu);
  }
  return(0);
}
