#include <bits/stdc++.h>
#define DEBUG if(0)

void readGot(int i, int n, int j, int got[][11])
{
  if (i == n) return;
  char comma; scanf("%d%c", &got[i][j], &comma);
  if (comma != ',')
  {
    got[i][10] = j + 1;
    readGot(i + 1, n, 0, got);
  }
  else readGot(i, n, j + 1, got);
}

void readResult(int size, int result[])
{
  if (size == -1) return;
  readResult(size - 1, result);
  scanf("%d", &result[size]);
}

int points(int i, int j, int player[], int result[])
{
  if (i == player[10]) return(0);
  DEBUG if (j < 6) printf("%d %d (%d, %d)\n", player[i], result[j], i, j);
  return(j == 6 ? points(i + 1, 0, player, result) : (player[i] == result[j]) + points(i, j + 1, player, result));
}

int sumWinner(int i, int n, int got[][11], int result[])
{
  if (i == n) return(0);
  return((points(0, 0, &got[i][0], result) >= 6) + sumWinner(i + 1, n, got, result));
}

int main()
{
  int n; scanf("%d", &n);
  int got[n][11], result[6];
  readGot(0, n, 0, got);
  readResult(6, result);

  int total = sumWinner(0, n, got, result);
  printf("Total de ganhadores: %d\n", total);

  return(0);
}