#include <bits/stdc++.h>
int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0};

int getDir(char dir)
{
  if (dir == 'N') return(0);
  if (dir == 'L') return(1);
  if (dir == 'S') return(2);
  return(3);
}

int main()
{
  int y, x, s;
  while (scanf("%d %d %d", &y, &x, &s) && !(!y && !x && !s))
  {
    char field[y][x + 1];
    for (int i = 0; i < y; i ++)
      scanf("\n%s", field[i]);

    int collected = 0, pi, pj, dir = 0;
    for (int i = 0; i < y; i ++)
      for (int j = 0; j < x; j ++)
        if (field[i][j] >= 'A' && field[i][j] <= 'Z')
        {
          pi = i; pj = j; dir = getDir(field[i][j]);
        }
    char instructions[s + 1]; scanf("\n%s", instructions);

    for (int i = 0; instructions[i]; i ++)
    {
      if (instructions[i] == 'D') dir ++;
      else if (instructions[i] == 'E') dir --;
      else
      {
        if (pi + dy[dir] >= 0 && pi + dy[dir] < y && pj + dx[dir] >= 0 && pj + dx[dir] < x && field[pi + dy[dir]][pj + dx[dir]] != '#')
        {
          pi += dy[dir];
          pj += dx[dir];
          collected += field[pi][pj] == '*';
          field[pi][pj] = '.';
        }
      }
      dir = (dir + 4) % 4;
    }

    printf("%d\n", collected);
  }
  return(0);
}