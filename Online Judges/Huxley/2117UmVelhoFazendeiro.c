#include <stdio.h>
#include <string.h>
int i, j;

void printMat(int n, int m, int mat[][m])
{
  for (i = 0; i < n; i ++)
    for (j = 0; j < m; j ++)
      printf("%d%c", mat[i][j], j < m - 1 ? ' ' : '\n');
}

void plant(int n, int m, int field[][m], int line, int *insecticide)
{
  for (j = 0; j < m; j ++)
    if (field[line][j] == 0)
    {
      field[line][j] = 1;
      *insecticide += 2;
    }
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int field[n][m]; for (i = 0; i < n; i ++) for (j = 0; j < m; j ++) scanf("%d", &field[i][j]); getchar();

  char command[100], end; int collected = 0, insecticide = 0;
  while (scanf("\n%s", command) != EOF)
  {
    if (!strcmp(command, "Colher"))
    {
      for (i = 0; i < n; i ++)
        for (j = 0; j < m; j ++)
          if (field[i][j] > 2)
          {
            collected ++;
            field[i][j] = 0;
          }
          else if (field[i][j] == -1)
          {
            field[i][j] = 0;
          }
    }
    else if (!strcmp(command, "Plantar"))
    {
      int line;
      while (scanf("%d%c", &line, &end) != EOF && end != '\n')
        plant(n, m, field, line, &insecticide);
      plant(n, m, field, line, &insecticide);
    }
    else if (!strcmp(command, "Temporada"))
    {
      for (i = 0; i < n; i ++)
        for (j = 0; j < m; j ++)
        {
          if (field[i][j] == 1) insecticide += 2;
          field[i][j] += field[i][j] > 0 && field[i][j] < 3 ? 1 : 0;
        }
    }
    else // Ataque
    {
      int k, w; scanf("%d %d", &k, &w);
      if (field[k][w]) field[k][w] = -1;
    }
  }

  printMat(n, m, field);
  printf("\nForam colhidos %d morangos.\nForam utilizados %dml de inseticida.\n", collected, insecticide);

  return(0);
}
/*
for (i = 0; i < n; i ++)
  for (j = 0; j < m; j ++)
*/