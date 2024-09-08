#include <bits/stdc++.h>
int mat[7][8 + 1]; char piece[7][7 + 1];

void printMatrix()
{
  for (int i = 0; i < 7; i ++)
    for (int j = 0; j < 8; j ++)
      printf("%2d%c", mat[i][j], j < 8 - 1 ? ' ' : '\n');
}

void printPiece()
{
  for (int i = 0; i < 7; i ++)
    for (int j = 0; j < 7; j ++)
      printf("%d%c", piece[i][j], j < 7 - 1 ? ' ' : '\n');
}

int bt(int i, int j)
{
  if (j == 8) { j = 0; i ++; }
  if (i == 7) return(1);
  if (mat[i][j] == -1) return(bt(i, j + 1));

  int ways = 0;
  if (i + 1 < 7 && mat[i + 1][j] != -1 && (piece[mat[i][j]][mat[i + 1][j]] || piece[mat[i + 1][j]][mat[i][j]]))
  {
    piece[mat[i][j]][mat[i + 1][j]] = piece[mat[i + 1][j]][mat[i][j]] = 0;
    int aux[2] = {mat[i][j], mat[i + 1][j]}; mat[i][j] = mat[i + 1][j] = -1;
    ways += bt(i, j + 1);
    mat[i][j] = aux[0]; mat[i + 1][j] = aux[1];
    piece[mat[i][j]][mat[i + 1][j]] = piece[mat[i + 1][j]][mat[i][j]] = 1;
  }
  if (j + 1 < 8 && mat[i][j + 1] != -1 && (piece[mat[i][j]][mat[i][j + 1]] || piece[mat[i][j + 1]][mat[i][j]]))
  {
    piece[mat[i][j]][mat[i][j + 1]] = piece[mat[i][j + 1]][mat[i][j]] = 0;
    int aux[2] = {mat[i][j], mat[i][j + 1]}; mat[i][j] = mat[i][j + 1] = -1;
    ways += bt(i, j + 1);
    mat[i][j] = aux[0]; mat[i][j + 1] = aux[1];
    piece[mat[i][j]][mat[i][j + 1]] = piece[mat[i][j + 1]][mat[i][j]] = 1;
  }
  return(ways);
}

int main()
{
  int t, r = 0; scanf("%d", &t);
  while (r < t)
  {
    memset(piece, 1, sizeof(piece));
    if (r ++) printf("\n");

    for (int i = 0; i < 7; i ++)
      for (int j = 0; j < 8; j ++)
        scanf("%d", &mat[i][j]);

    int ans = bt(0, 0);

    printf("Teste %d\n%d\n", r, ans);
  }
  return(0);
}