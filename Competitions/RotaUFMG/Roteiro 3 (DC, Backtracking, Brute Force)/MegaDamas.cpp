#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
int board[20][20];
int dx[4] = {1, 1, -1, -1}, dy[4] = {1, -1, 1, -1};

int valid(int i, int y, int j, int x)
{
  return(!(i < 0 || j < 0 || i >= y || j >= x || board[i][j] != 0));
}

int bt(int i, int y, int j, int x)
{
  int ate = 0;
  for (int k = 0; k < 4; k ++)
    if (valid(i + 2*dy[k], y, j + 2*dx[k], x) && board[i + dy[k]][j + dx[k]] == 2)
    {
      board[i + dy[k]][j + dx[k]] = 0;
      ate = max(ate, 1 + bt(i + 2*dy[k], y, j + 2*dx[k], x));
      board[i + dy[k]][j + dx[k]] = 2;
    }
  return(ate);
}

int main()
{
  int y, x;
  while (scanf("%d %d", &y, &x) && !(!y && !x))
  {
    memset(board, 0, sizeof(board));
    for (int i = y - 1, k = 0; i >= 0; i --, k = 1 - k)
      for (int j = k; j < x; j += 2)
      {
        int piece; scanf("%d", &piece);
        board[i][j] = piece;
      }

    DEBUG for (int i = 0; i < y; i ++)
      for (int j = 0; j < x; j ++)
        printf("%d%c", board[i][j], j < x - 1 ? ' ' : '\n');
    DEBUG printf("\n");

    int ate = 0;
    for (int i = 0; i < y; i ++)
      for (int j = 0; j < x; j ++)
        if (board[i][j] == 1)
        {
          board[i][j] = 0;
          ate = max(ate, bt(i, y, j, x));
          board[i][j] = 1;
        }

    printf("%d\n", ate);
  }

  return(0);
}