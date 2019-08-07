#include <bits/stdc++.h>
#define DEBUG if(0)

void printMatrix(int m[][500], int y, int x)
{
  for (int i = 0; i < y; i ++)
    for (int j = 0; j < x; j ++)
      printf("%d%c", m[i][j], j < x - 1 ? ' ' : '\n');
}

int main()
{
  int y, x; scanf("%d %d\n", &y, &x);
  char table[y][x + 1];
  for (int i = 0; i < y; i ++)
    scanf("%s\n", table[i]);

  int horizontal[500][500], vertical[500][500]; char prev;
  for (int i = 0; i < y; i ++)
  {
    prev = table[i][0];
    horizontal[i][0] = 0;
    for (int j = 1; j < x; j ++)
    {
      horizontal[i][j] = horizontal[i][j - 1];
      if (prev == '.' && table[i][j] == '.')
        horizontal[i][j] ++;
      prev = table[i][j];
    }
  }
  for (int i = 0; i < x; i ++)
  {
    prev = table[0][i];
    vertical[0][i] = 0;
    for (int j = 1; j < y; j ++)
    {
      vertical[j][i] = vertical[j - 1][i];
      if (prev == '.' && table[j][i] == '.')
        vertical[j][i] ++;
      prev = table[j][i];
    }
  }

  for (int i = 1; i < y; i ++)
    for (int j = 0; j < x; j ++)
      horizontal[i][j] += horizontal[i - 1][j];
  for (int i = 1; i < x; i ++)
    for (int j = 0; j < y; j ++)
      vertical[j][i] += vertical[j][i - 1];

  DEBUG {printMatrix(horizontal, y, x); printf("\n");
  printMatrix(vertical, y, x);}

  int queries; scanf("%d", &queries);
  while (queries --)
  {
    int li, lj, hi, hj; scanf("%d %d %d %d", &li, &lj, &hi, &hj); li --; lj --; hi --; hj --;
    int ans = horizontal[hi][hj] + vertical[hi][hj];
    if (li)
    {
      ans -= horizontal[li - 1][hj] + vertical[li - 1][hj];
      for (int j = lj; j <= hj; j ++)
        ans -= (table[li][j] == '.') && (table[li - 1][j] == '.');
    }
    if (lj)
    {
      ans -= horizontal[hi][lj - 1] + vertical[hi][lj - 1];
      for (int i = li; i <= hi; i ++)
        ans -= (table[i][lj] == '.') && (table[i][lj - 1] == '.');
    }
    if (li && lj)
      ans += horizontal[li - 1][lj - 1] + vertical[li - 1][lj - 1];
    printf("%d\n", ans);
  }

  return(0);
}