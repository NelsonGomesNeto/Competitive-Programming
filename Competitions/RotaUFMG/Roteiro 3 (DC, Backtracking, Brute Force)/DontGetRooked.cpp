#include <bits/stdc++.h>
using namespace std;
int size;
char board[4][4 + 1];

int canPut(int i, int j)
{
  int left, right, up, down; left = right = up = down = 1;
  for (int k = 0; k < size; k ++)
  {
    if (j + k < size && board[i][j + k] == 'X') right = 0;
    if (j - k >= 0 && board[i][j - k] == 'X') left = 0;
    if (i + k < size && board[i + k][j] == 'X') down = 0;
    if (i - k >= 0 && board[i - k][j] == 'X') up = 0;
    if (j + k < size && right && board[i][j + k] == 'R') return(0);
    if (j - k >= 0 && left && board[i][j - k] == 'R') return(0);
    if (i + k < size && down && board[i + k][j] == 'R') return(0);
    if (i - k >= 0 && up && board[i - k][j] == 'R') return(0);
  }
  return(1);
}

int bruteForce(int i, int j)
{
  int put = 0, notPut = 0;
  if (i == size)
    return(0);
  else if (board[i][j] != '.')
  {
    if (j == size - 1) return(bruteForce(i + 1, 0));
    else return(bruteForce(i, j + 1));
  }

  if (canPut(i, j))
  {
    board[i][j] = 'R';
    if (j == size - 1) put = 1 + bruteForce(i + 1, 0);
    else put = 1 + bruteForce(i, j + 1);
    board[i][j] = '.';
  }
  if (j == size - 1) notPut = bruteForce(i + 1, 0);
  else notPut = bruteForce(i, j + 1);

  return(max(put, notPut));
}

int main()
{
  while (scanf("%d", &size) && size)
  {
    for (int i = 0; i < size; i ++)
      scanf("\n%s", board[i]);

    int ans = bruteForce(0, 0);
    printf("%d\n", ans);
  }
  return(0);
}