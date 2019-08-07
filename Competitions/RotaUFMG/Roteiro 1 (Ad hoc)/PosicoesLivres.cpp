#include <bits/stdc++.h>
using namespace std;

int main()
{
  int x, y, sub;
  while (scanf("%d %d %d", &x, &y, &sub) && !(!x && !y && !sub))
  {
    int mat[y][x];
    for (int i = 0; i < y; i ++) for (int j = 0; j < x; j ++) mat[i][j] = 1;
    while (sub -- > 0)
    {
      int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2); x1 --; y1 --; x2 --; y2 --;
      for (int i = min(y1, y2); i <= max(y1, y2); i ++)
        for (int j = min(x1, x2); j <= max(x1, x2); j ++)
          mat[i][j] = 0;
    }
    int spots = 0;
    for (int i = 0; i < y; i ++)
      for (int j = 0; j < x; j ++)
      {
        //printf("%d%c", mat[i][j], j < x - 1 ? ' ' : '\n');
        spots += mat[i][j];
      }

    if (!spots)
      printf("There is no empty spots.\n");
    else if (spots == 1)
      printf("There is one empty spot.\n");
    else
      printf("There are %d empty spots.\n", spots);
  }
  return(0);
}