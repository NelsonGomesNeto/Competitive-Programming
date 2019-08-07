#include <bits/stdc++.h>
#define DEBUG if(0)
int mat[100][100], sum[100][100];

void printMat(int m[][100], int size)
{
  for (int i = 0; i < size; i ++)
    for (int j = 0; j < size; j ++)
      printf("%d%c", m[i][j], j < size - 1 ? ' ' : '\n');
}

int main()
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      scanf("%d", &mat[i][j]);

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      sum[i][j] = mat[i][j];
      if (i) sum[i][j] += sum[i - 1][j];
      if (j) sum[i][j] += sum[i][j - 1];
      if (i && j) sum[i][j] -= sum[i - 1][j - 1];
    }

  DEBUG printMat(sum, n);

  int bestSum = sum[0][0];
  for (int li = 0; li < n; li ++)
    for (int lj = 0; lj < n; lj ++)
      for (int hi = li; hi < n; hi ++)
        for (int hj = lj; hj < n; hj ++)
        {
          int now = sum[hi][hj];
          if (li) now -= sum[li - 1][hj];
          if (lj) now -= sum[hi][lj - 1];
          if (li && lj) now += sum[li - 1][lj - 1];
          DEBUG printf("%d %d %d %d %d\n", li, lj, hi, hj, now);
          if (now > bestSum) bestSum = now;
        }

  printf("%d\n", bestSum);

  return(0);
}