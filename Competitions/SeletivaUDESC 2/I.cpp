#include <bits/stdc++.h>
int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};
int has[10][10][10], original[10][10][10];

int valid(int pos)
{
  return(pos >= 0 && pos <= 9);
}

int advantage(int i, int j, int k)
{
  int save = 0;
  for (int lol = 0; lol < 6; lol ++)
    if (valid(i + dx[lol]) && valid(j + dy[lol]) && valid(k + dz[lol]) && has[i + dx[lol]][j + dy[lol]][k + dz[lol]])
      save ++;
  return(save >= 3);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(has, 0, sizeof(has)); memset(original, 0, sizeof(original));
    int x, y, z;
    int f; scanf("%d", &f);
    int block[10000][3];
    for (int i = 0; i < f; i ++)
    {
      scanf("%d %d %d", &x, &y, &z);
      block[i][0] = x; block[i][1] = y; block[i][2] = z;
      has[x][y][z] = original[x][y][z] = 1;
    }
    for (int w = 0; w < 1000; w ++)
      for (int i = 0; i <= 9; i ++)
        for (int j = 0; j <= 9; j ++)
          for (int k = 0; k <= 9; k ++)
            if (!has[i][j][k] && advantage(i, j, k))
            {
              block[f][0] = i; block[f][1] = j; block[f][2] = k;
              has[i][j][k] = 1;
              f ++;
            }

    int minTime = 0;
    for (int i = 0; i < f; i ++)
      for (int k = 0; k < 6; k ++)
        if (valid(block[i][0]+dx[k]) && valid(block[i][1]+dy[k]) && valid(block[i][2]+dz[k]))
          minTime += !has[block[i][0]+dx[k]][block[i][1]+dy[k]][block[i][2]+dz[k]];
        else
          minTime ++;
    printf("%d\n", minTime);
  }
  return(0);
}