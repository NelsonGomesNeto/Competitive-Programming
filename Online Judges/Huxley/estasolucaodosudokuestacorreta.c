#include <stdio.h>

int check(int num)
{
  if (num != 1 && num != 2 && num != 3)
  {
    if (num != 4 && num != 5 && num != 6)
    {
      if (num != 7 && num != 8 && num != 9)
      {
        return(1);
      }
    }
  }
  return(0);
}

int main()
{
  int testes, run; scanf("%d", &testes);
  for (run = 1; run <= testes; run ++)
  {
    if (run > 1) { printf("\n"); }
    int sudoku[9][9], j, i, jM, iM, nope = 0, num, vezes;
    for (j = 0; j < 9; j ++)
    {
      for (i = 0; i < 9; i ++)
      {
        scanf("%d", &sudoku[j][i]);
        if (check(sudoku[j][i]) == 1)
        {
          nope ++;
        }
      }
    }
    for (j = 0; j < 9; j ++) //Checando cada linha
    {
      for (num = 1; num <= 9; num ++)
      {
        vezes = 0;
        for (i = 0; i < 9; i ++)
        {
          if (sudoku[j][i] == num)
          {
            vezes ++;
          }
        }
        if (vezes > 1)
        {
          nope ++;
        }
      }
    }
    for (i = 0; i < 9; i ++) //Checando cada coluna
    {
      for (num = 1; num <= 9; num ++)
      {
        vezes = 0;
        for (j = 0; j < 9; j ++)
        {
          if (sudoku[j][i] == num)
          {
            vezes ++;
          }
        }
        if (vezes > 1)
        {
          nope ++;
        }
      }
    }
    for (j = 1; j < 9; j += 3) //Checando os quadrados
    {
      for (i = 1; i < 9; i += 3)
      {
        for (num = 1; num <= 9; num ++)
        {
          vezes = 0;
          for (jM = j - 1; jM < j + 2; jM ++)
          {
            for (iM = i - 1; iM < i + 2; iM ++)
            {
              //printf("%d ", sudoku[jM][iM]);
              if (sudoku[jM][iM] == num)
              {
                vezes ++;
              }
            }
            //printf("\n");
          }
          if (vezes > 1)
          {
            nope ++;
          }
        }
      }
    }
    printf("Instancia %d\n", run);
    if (nope == 0) { printf("SIM\n"); }
    else { printf("NAO\n"); }
  }
  return(0);
}
