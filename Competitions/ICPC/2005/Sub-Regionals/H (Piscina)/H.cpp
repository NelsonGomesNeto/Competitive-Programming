#include <bits/stdc++.h>

/*
Pieces will be 1x1, 3x3 and 6x6
*/
const int maxSize = 50 * 100 / 5; int x, y, z, p, m, g;
bool bottom[maxSize][maxSize], sidex[2][maxSize][maxSize], sidey[2][maxSize][maxSize];
// bool bottom[x][y], sidex[2][x][z], sidey[2][y][z];

void fill(bool mat[maxSize][maxSize], int si, int sj, int size)
{
  for (int i = si; i < si + size; i ++)
    for (int j = sj; j < sj + size; j ++)
      mat[i][j] = true;
}

void tryFill(bool mat[maxSize][maxSize], int i, int j, int endi, int endj)
{
  if (g && i + 6 <= endi && j + 6 <= endj)
    fill(mat, i, j, 6), g --;
  else if (m && i + 3 <= endi && j + 3 <= endj)
    fill(mat, i, j, 3), m --;
  else if (p && i + 1 <= endi && j + 1 <= endj)
    fill(mat, i, j, 1), p --;
}

int main()
{
  double a, b, c;
  while (scanf("%lf %lf %lf", &a, &b, &c) && (a || b || c))
  {
    x = a * 100 / 5, y = b * 100 / 5, z = c * 100 / 5;
    scanf("%d %d %d", &p, &m, &g); int op = p, om = m, og = g;
    
    memset(bottom, false, sizeof(bottom)); memset(sidex, false, sizeof(sidex)); memset(sidey, false, sizeof(sidey));

    for (int i = 0; i < x; i ++)
      for (int j = 0; j < y; j ++)
        if (!bottom[i][j])
          tryFill(bottom, i, j, x, y);
    for (int k = 0; k < 2; k ++)
    {
      for (int i = 0; i < x; i ++)
        for (int j = 0; j < z; j ++)
          if (!sidex[k][i][j])
            tryFill(sidex[k], i, j, x, z);
      for (int i = 0; i < y; i ++)
        for (int j = 0; j < z; j ++)
          if (!sidey[k][i][j])
            tryFill(sidey[k], i, j, y, z);
    }
    bool can = true;
    for (int i = 0; i < x; i ++) for (int j = 0; j < y; j ++) if (!bottom[i][j]) can = false;
    for (int k = 0; k < 2; k ++)
    {
      for (int i = 0; i < x; i ++) for (int j = 0; j < z; j ++) if (!sidex[k][i][j]) can = false;
      for (int i = 0; i < y; i ++) for (int j = 0; j < z; j ++) if (!sidey[k][i][j]) can = false;
    }
    // printf("%d %d %d | %d %d %d\n", op - p, om - m, og - g, x, y, z);
    if (can) printf("%d %d %d\n", op - p, om - m, og - g);
    else printf("impossivel\n");
  }
  return(0);
}