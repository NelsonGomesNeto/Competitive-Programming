#include <stdio.h>

void row(int y, int x, int b[][x], int i)
{
  int j;
  for (j = 0; j < x; j ++)
    b[i][j] --;
}

void column(int y, int x, int b[][x], int j)
{
  int i;
  for (i = 0; i < y; i ++)
    b[i][j] --;
}

int findSmallRow(int y, int x, int b[][x], int i)
{
  int j, small = b[i][0];
  for (j = 1; j < x; j ++)
    if (b[i][j] < small)
      small = b[i][j];

  return(small);
}

int findSmallColumn(int y, int x, int b[][x], int j)
{
  int i, small = b[0][j];
  for (i = 1; i < y; i ++)
    if (b[i][j] < small)
      small = b[i][j];

  return(small);
}

int solved(int y, int x, int b[][x])
{
  int i, j;
  for (i = 0; i < y; i ++)
    for (j = 0; j < x; j ++)
      if (b[i][j] != 0)
        return(0);

  return(1);
}

void solve(int y, int x, int b[][x])
{
  int i, j, moves = 0;
  int seq[100000][2];

  int aux = -1;
  while (aux != moves)
  {
    aux = moves;
    int doX, doY, small = 99999999;
    for (i = 0; i < y; i ++)
      for (j = 0; j < x; j ++)
        if (b[i][j] != 0 && b[i][j] < small)
        {
          small = b[i][j];
          doX = j; doY = i;
        }

    if (y > x)
    {
      int minCol = findSmallColumn(y, x, b, doX);
      while (minCol > 0)
      {
        column(y, x, b, doX);
        seq[moves][0] = 1; seq[moves][1] = doX + 1;
        moves ++; minCol --;
      }

      int minRow = findSmallRow(y, x, b, doY);
      while (minRow > 0)
      {
        row(y, x, b, doY);
        seq[moves][0] = 0; seq[moves][1] = doY + 1;
        moves ++; minRow --;
      }
    }
    else
    {
      int minRow = findSmallRow(y, x, b, doY);
      while (minRow > 0)
      {
        row(y, x, b, doY);
        seq[moves][0] = 0; seq[moves][1] = doY + 1;
        moves ++; minRow --;
      }

      int minCol = findSmallColumn(y, x, b, doX);
      while (minCol > 0)
      {
        column(y, x, b, doX);
        seq[moves][0] = 1; seq[moves][1] = doX + 1;
        moves ++; minCol --;
      }
    }
  }

  if (!solved(y, x, b))
    printf("-1\n");
  else
  {
    printf("%d\n", moves);
    for (i = 0; i < moves; i ++)
      printf("%s %d\n", seq[i][0] == 0 ? "row" : "col", seq[i][1]);
  }
}

int main()
{
  int y, x; scanf("%d %d", &y, &x);
  int board[y][x], i, j;
  for (i = 0; i < y; i ++)
    for (j = 0; j < x; j ++)
      scanf("%d", &board[i][j]);

  solve(y, x, board);

  return(0);
}
