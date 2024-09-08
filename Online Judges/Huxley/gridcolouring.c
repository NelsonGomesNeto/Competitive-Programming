#include <stdio.h>
#define MAX 1000
int dX[4] = {1, -1, 0, 0};
int dY[4] = {0, 0, 1, -1};

void floodFill(char field[][MAX], char barrier, char color, int x, int y)
{
  int i;
  for (i = 0; i < 4; i ++)
    if (x + dX[i] >= 0 && x + dX[i] < MAX
    &&  y + dY[i] >= 0 && y + dY[i] < MAX
    && field[x + dX[i]][y + dY[i]] != barrier && field[x + dX[i]][y + dY[i]] != color
    && field[x + dX[i]][y + dY[i]] != '\0')
    {
      field[x + dX[i]][y + dY[i]] = color;
      floodFill(field, barrier, color, x + dX[i], y + dY[i]);
    }
}

void cleanCampo(char field[][MAX])
{
  int i, j;
  for (i = 0; i < MAX; i ++)
    for (j = 0; j < MAX; j ++)
      field[i][j] = '\0';
}

void printCampo(char field[][MAX], int endY)
{
  int i, j;
  for (i = 0; i < endY; i ++)
    for (j = 0; j < MAX; j ++)
    {
      if (field[i][j] != '\0')
        printf("%c", field[i][j]);
      else
      {
        printf("\n");
        break;
      }
    }
}

int main()
{
  char campo[MAX][MAX], underscore;
  int i, j;
  cleanCampo(campo);

  while (scanf("%c", &campo[i][j]) != EOF)
  {
    if (campo[i][j] == '_')
    {
      int limitY = i;
      campo[i][j] = '\0';
      char barrier = '\0';

      for (i = 0; i < limitY; i ++)
      {
        for (j = 0; j < MAX && campo[i][j] != '\0'; j ++)
        {
          if (barrier != '\0' && campo[i][j] == barrier)
            barrier = '\0';

          if (campo[i][j] != ' ' && barrier == '\0')
            barrier = campo[i][j];

          if (campo[i][j] != barrier && campo[i][j] != ' '
           && campo[i][j] != '\n' && barrier != '\0')
            floodFill(campo, barrier, campo[i][j], i, j);
        }
      }

      printCampo(campo, limitY); printf("_");
      while (scanf("%c", &underscore) != EOF && underscore != '\n')
        printf("_");
      printf("\n"); underscore = '\0';

      cleanCampo(campo); i = 0; j = 0;
    }
    else if (campo[i][j] == '\n')
    {
      campo[i][j] = '\0';
      i ++; j = 0;
    }
    else
      j ++;
  }

  return(0);
}
