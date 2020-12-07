#include <bits/stdc++.h>
using namespace std;

void read(int n, int a[])
{
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
}

int main()
{
  int n, m, h; scanf("%d %d %d", &n, &m, &h);
  int columnMaxHeight[m]; read(m, columnMaxHeight);
  int maxLeftHeight[n]; read(n, maxLeftHeight);
  int mat[n][m];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  int a[n][m], b[n][m];
  for (int j = 0; j < m; j ++)
    for (int i = 0; i < n; i ++)
      a[i][j] = columnMaxHeight[j] * mat[i][j];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      b[i][j] = maxLeftHeight[i] * mat[i][j];

  int result[n][m];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      result[i][j] = min(a[i][j], b[i][j]);

  for (int i = 0; i < n; i ++)
  {
    for (int j = 0; j < m; j ++)
      printf("%d ", result[i][j]);
    printf("\n");
  }

  return(0);
}