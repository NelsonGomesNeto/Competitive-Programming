#include <stdio.h>

char mar[200][200]; int nope;

int check(int y, int x, int limitY, int limitX)
{
  if (x + 1 < limitX && mar[y][x + 1] == 'p')
  {
    mar[y][x + 1] = 'c';
    check(y, x + 1, limitY, limitX);
  }
  if (x + 1 < limitX && mar[y][x + 1] == '#')
  {
    mar[y][x + 1] = 'c'; nope ++;
  }
  if (x - 1 >= 0 && mar[y][x - 1] == 'p')
  {
    mar[y][x - 1] = 'c';
    check(y, x - 1, limitY, limitX);
  }
  if (x - 1 >= 0 && mar[y][x - 1] == '#')
  {
    mar[y][x - 1] = 'c'; nope ++;
  }
  if (y + 1 < limitY && mar[y + 1][x] == 'p')
  {
    mar[y + 1][x] = 'c';
    check(y + 1, x, limitY, limitX);
  }
  if (y + 1 < limitY && mar[y + 1][x] == '#')
  {
    mar[y + 1][x] = 'c'; nope ++;
  }
  if (y - 1 >= 0 && mar[y - 1][x] == 'p')
  {
    mar[y - 1][x] = 'c';
    check(y - 1, x, limitY, limitX);
  }
  if (y - 1 >= 0 && mar[y - 1][x] == '#')
  {
    mar[y - 1][x] = 'c'; nope ++;
  }
  return(1);
}

int main()
{
  int Y, X; scanf("%d %d", &Y, &X);
  int j, i;
  for (j = 0; j < Y; j ++)
  {
    getchar();
    for (i = 0; i < X; i ++)
    {
      scanf("%c", &mar[j][i]);
    }
  }
  int comandos, atkY, atkX; scanf("%d", &comandos);
  for (i = 0; i < comandos; i ++)
  {
    scanf("%d %d", &atkY, &atkX);
    atkY --; atkX --;
    if (mar[atkY][atkX] == '#')
    {
      mar[atkY][atkX] = 'p';
    }
  }
  int destruidos = 0;
  for (j = 0; j < Y; j ++)
  {
    for (i = 0; i < X; i ++)
    {
      if (mar[j][i] == 'p')
      {
        mar[j][i] = 'c';
        nope = 0;
        check(j, i, Y, X);
        if (nope == 0)
        {
          destruidos ++;
        }
      }
    }
  }
  printf("%d\n", destruidos);
  return(0);
}
