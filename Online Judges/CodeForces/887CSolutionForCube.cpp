#include <bits/stdc++.h>
#define DEBUG if(1)

int main()
{
  int cube[6][2][2 + 1]; int i, j, k;
  for (i = 0; i < 6; i ++)
    for (j = 0; j < 2; j ++)
      for (k = 0; k < 2; k ++)
        scanf("%d", &cube[i][j][k]);

  for (i = 0; i < 2; i ++)
  {
    int aux = cube[5][i][0];
    cube[5][i][0] = cube[5][i][1];
    cube[5][i][1] = aux;
    aux = cube[2][0][i];
    cube[2][0][i] = cube[2][1][i];
    cube[2][1][i] = aux;
    aux = cube[3][i][0];
    cube[3][i][0] = cube[3][i][1];
    cube[3][i][1] = aux;
    // aux = cube[3][0][i];
    // cube[3][0][i] = cube[3][1][i];
    // cube[3][1][i] = aux;
    aux = cube[4][i][0];
    cube[4][i][0] = cube[4][i][1];
    cube[4][i][1] = aux;
  }
  // int aux1, aux2, aux3, aux4;
  // aux1 = cube[3][0][0]; aux2 = cube[3][0][1]; aux3 = cube[3][1][1]; aux4 = cube[3][1][0];
  // cube[3][0][0] = aux2;
  // cube[3][0][1] = aux3;
  // cube[3][1][0] = aux1;
  // cube[3][1][1] = aux4;
  // aux1 = cube[4][0][0]; aux2 = cube[4][0][1]; aux3 = cube[4][1][1]; aux4 = cube[4][1][0];
  // cube[4][0][0] = aux4;
  // cube[4][0][1] = aux1;
  // cube[4][1][0] = aux3;
  // cube[4][1][1] = aux2;

  DEBUG {
    for (i = 0; i < 6; i ++)
      for (j = 0; j < 2; j ++)
      {
        for (k = 0; k < 2; k ++)
          printf("%d", cube[i][j][k]);
        printf("\n");
      }
  }

  int completed = 0, halved = 0, t[2] = {0, 0}; int tire[2][9];
  for (i = 0; i < 6; i ++)
  {
    int color = cube[i][0][0]; int now = 0;
    for (j = 0; j < 2; j ++)
    {
      for (k = 0; k < 2; k ++)
        now += cube[i][j][k] == color;
    }
    if (now == 4) completed ++;
    else
    {
      if (cube[i][0][0] == cube[i][0][1])
      {
        tire[0][t[0] ++] = cube[i][0][0];
        tire[0][t[0] ++] = cube[i][0][0];
        tire[1][t[1] ++] = cube[i][1][0];
        tire[1][t[1] ++] = cube[i][1][0];
        halved ++;
        halved ++;
      }
      if (cube[i][0][0] == cube[i][1][0])
      {
        tire[0][t[0] ++] = cube[i][0][0];
        tire[0][t[0] ++] = cube[i][0][0];
        tire[1][t[1] ++] = cube[i][0][1];
        tire[1][t[1] ++] = cube[i][0][1];
        halved ++;
        halved ++;
      }
    }
  }

  DEBUG {
    for (i = 0; i < 2; i ++)
    {
      for (j = 0; j < 8; j ++)
        printf("%d", tire[i][j]);
      printf("\n");
    }
  }

  int perfect = 0;
  if (halved == 8)
  {
    for (j = 0; j < 8; j ++)
    {
      DEBUG printf("%d %d\n", tire[0][j], tire[1][(j + 2) % 8]);
      perfect += (tire[0][j] == tire[1][(j + 2) % 8]);
    }
    if (perfect != 8)
    {
      perfect = 0;
      for (j = 0; j < 8; j ++)
      {
        DEBUG printf("%d %d\n", tire[0][j], tire[1][(j + 6) % 8]);
        perfect += (tire[0][j] == tire[1][(j + 6) % 8]);
      }
    }
  }
  if (perfect == 8) perfect = 1;

  if (completed == 2 && perfect)
    printf("YES\n");
  else
    printf("NO\n");

  return(0);
}