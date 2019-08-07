#include <bits/stdc++.h>
int mat[100][100];

void build(int lo, int hi, int num)
{
  if (lo > hi) return;
  for (int i = lo; i <= hi; i ++)
  {
    mat[i][lo] = num;
    mat[i][hi] = num;
    mat[lo][i] = num;
    mat[hi][i] = num;
  }
  build(lo + 1, hi - 1, num + 1);
}

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    build(0, n - 1, 1);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n ; j ++)
      {
        if (j) printf("%s", mat[i][j] < 10 ? "   " : mat[i][j] < 100 ? "  " : " ");
        else printf("  ");
        printf("%d", mat[i][j]);
        if (j == n - 1) printf("\n");
      }

    printf("\n");
  }

  return(0);
}