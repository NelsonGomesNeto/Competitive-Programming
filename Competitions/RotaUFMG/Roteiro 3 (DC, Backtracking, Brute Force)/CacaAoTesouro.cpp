#include <bits/stdc++.h>
#define DEBUG if(0)

int valid(int k, int m, int x, int y, int n)
{
  return(!(x + k < 0 || x + k >= n || y + m < 0 || y + m >= n));
}

int main()
{
  int n, k; scanf("%d %d", &n, &k);

  int map[n][n]; memset(map, 0, sizeof(map));
  for (int i = 0; i < k; i ++)
  {
    int x, y, d; scanf("%d %d %d", &x, &y, &d);
    y = n - 1 - y;
    for (int k = 0; k <= d; k ++)
    {
      if (valid(k, d - k, x, y, n))
        map[y + (d - k)][x + k] ++;
      if ((d - k) && valid(k, k - d, x, y, n))
        map[y + (k - d)][x + k] ++;
      if (k && valid(-k, d - k, x, y, n))
        map[y + (d - k)][x - k] ++;
      if (k && (d - k) && valid(-k, k - d, x, y, n))
        map[y + (k - d)][x - k] ++;
    }
  }

  DEBUG for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      printf("%d%c", map[i][j], j < n - 1 ? ' ' : '\n');

  int best = 0, equal = 0, bx, by;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      if (map[i][j] > best)
      {
        best = map[i][j];
        bx = j;
        by = n - 1 - i;
        equal = 0;
      }
      else if (map[i][j] == best)
        equal = 1;

  if (equal)
    printf("-1 -1\n");
  else
    printf("%d %d\n", bx, by);

  return(0);
}