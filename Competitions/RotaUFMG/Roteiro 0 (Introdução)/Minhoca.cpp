#include <bits/stdc++.h>

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int mat[n][m];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  int best = 0, sum;
  for (int i = 0; i < n; i ++)
  {
    sum = 0;
    for (int j = 0; j < m; j ++)
      sum += mat[i][j];
    if (sum > best) best = sum;
  }

  for (int j = 0; j < m; j ++)
  {
    sum = 0;
    for (int i = 0; i < n; i ++)
      sum += mat[i][j];
    if (sum > best) best = sum;
  }

  printf("%d\n", best);

  return(0);
}