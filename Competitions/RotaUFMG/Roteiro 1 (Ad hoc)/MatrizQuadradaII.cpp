#include <bits/stdc++.h>
int mat[100][100];

void build(int lo, int hi)
{
  if (lo > hi) return;
  for (int i = lo, at = 1; i <= hi; i ++, at ++)
  {
    mat[lo][i] = at;
    mat[i][lo] = at;
    mat[hi - (at - 1)][hi] = at;
    mat[hi][hi - (at - 1)] = at;
  }
  build(lo + 1, hi - 1);
}

int main()
{
  int n;
  while (scanf("%d", &n) && n)
  {
    build(0, n - 1);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
      {
        if (j) printf("%s", mat[i][j] < 10 ? "   " : mat[i][j] < 100 ? "  " : " ");
        else printf("%s", mat[i][j] < 10 ? "  " : mat[i][j] < 100 ? " " : "\0");
        printf("%d", mat[i][j]);
        if (j == n - 1) printf("\n");
      }
    printf("\n");
  }

  return(0);
}