#include <bits/stdc++.h>
char mat[100][100 + 1], target[10 + 1] = "ALLIZZWELL";
int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int valid(int at, int i, int y, int j, int x)
{
  return(!(i < 0 || j < 0 || i >= y || j >= x || mat[i][j] != target[at]));
}

int bt(int at, int i, int y, int j, int x)
{
  if (!target[at]) return(1);

  for (int k = 0; k < 8; k ++)
    if (valid(at, i + dy[k], y, j + dx[k], x))
    {
      mat[i + dy[k]][j + dx[k]] = '.';
      if (bt(at + 1, i + dy[k], y, j + dx[k], x))
        return(1);
      mat[i + dy[k]][j + dx[k]] = target[at];
    }
  return(0);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int y, x; scanf("%d %d", &y, &x);
    for (int i = 0; i < y; i ++)
      scanf("\n%s", mat[i]);

    int can = 0;
    for (int i = 0; i < y && !can; i ++)
      for (int j = 0; j < x && !can; j ++)
        if (mat[i][j] == target[0])
        {
          mat[i][j] = '.';
          if (bt(1, i, y, j, x))
            can = 1;
          mat[i][j] = target[0];
        }

    printf("%s\n", can ? "YES" : "NO");
  }
  return(0);
}