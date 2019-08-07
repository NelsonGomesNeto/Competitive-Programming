#include <stdio.h>
#define yAtual d[(*b).dir].y
#define xAtual d[(*b).dir].x

int Y, X;

struct robo
{
  int y, x, dir;
};

struct direction
{
  int y, x;
};

int initialDir(char p, int *d)
{
  /*
    0
  3   1
    2
  */
  if (p == 'N')
  {
    (*d) = 0; return(1);
  }
  if (p == 'L')
  {
    (*d) = 1; return(1);
  }
  if (p == 'S')
  {
    (*d) = 2; return(1);
  }
  if (p == 'O')
  {
    (*d) = 3; return(1);
  }
  return(0);
}

int move(char map[Y][X], struct robo *b, struct direction d[], char com)
{
  if (com == 'E')
  {
    (*b).dir --;
    if ((*b).dir < 0) { (*b).dir = 3; }
    return(0);
  }
  if (com == 'D')
  {
    (*b).dir ++;
    if ((*b).dir > 3) { (*b).dir = 0; }
    return(0);
  }
  if (com == 'F')
  {
    int newY = (*b).y + yAtual, newX = (*b).x + xAtual;
    if (newY >= 0 && newY < Y
    &&  newX >= 0 && newX < X
    &&  map[newY][newX] != '#')
    {
      (*b).y = newY; (*b).x = newX;
      if (map[newY][newX] == '*')
      {
        map[newY][newX] = '.';
        return(1);
      }
      return(0);
    }
  }
  return(0);
}

int main()
{
  struct direction di[4];
  di[0].y = -1, di[0].x = 0;
  di[1].y = 0, di[1].x = 1;
  di[2].y = 1, di[2].x = 0;
  di[3].y = 0, di[3].x = -1;
  int comandos;
  while (scanf("%d %d %d", &Y, &X, &comandos)
  && !(Y == 0 && X == 0 && comandos == 0))
  {
    char mapa[Y][X], i, j; struct robo r;
    for (i = 0; i < Y; i ++)
    {
      for (j = 0; j < X; j ++)
      {
        scanf("%c", &mapa[i][j]);
        if (mapa[i][j] == ' ' || mapa[i][j] == '\n') { j --; continue; }
        //Entrada bugada, isso é necessário '-' .-.
        else if (initialDir(mapa[i][j], &r.dir))
        {
          mapa[i][j] = '.';
          r.x = j; r.y = i;
        }
      }
    }
    int figurinhas = 0; char oper;
    while (comandos > 0)
    {
      scanf("%c", &oper);
      if (oper == ' ' || oper == '\n') { continue; }
      //Entrada bugada, isso é necessário '-' .-.
      figurinhas += move(mapa, &r, di, oper);
      comandos --;
    }
    printf("%d\n", figurinhas);
  }
  return(0);
}
