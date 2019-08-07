#include <stdio.h>

int sudoku[10][10];

int getMeio(int n)
{
  if (n < 3)
  {
    return(0);
  }
  if (n < 6)
  {
    return(3);
  }
  return(6);
}

void zeraContador(int array[])
{
  int i;
  for (i = 1; i < 10; i ++)
  {
    array[i] = 0;
  }
}

void printar()
{
  int pi, pj;
  for (pi = 0; pi < 9; pi ++)
  {
    for (pj = 0; pj < 9; pj ++)
    {
      printf("%d", sudoku[pi][pj]);
    } printf("\n");
  }
}

void solve()
{
  int i, j, iM, jM, fimI, fimJ, numeros[10], aux;
  for (i = 0; i < 9; i ++)
  {
    for (j = 0; j < 9; j ++)
    {
      if (sudoku[i][j] == 0)
      {
        zeraContador(numeros);

        for (iM = 0; iM < 9; iM ++) //Verifica a coluna
        {
          numeros[sudoku[iM][j]] ++;
        }

        for (jM = 0; jM < 9; jM ++) //Verifica a linha
        {
          numeros[sudoku[i][jM]] ++;
        }

        iM = getMeio(i); fimI = iM + 3;
        jM = getMeio(j); fimJ = jM + 3;
        for (iM = fimI - 3; iM < fimI; iM ++) //Verifica o meio
        {
          for (jM = fimJ - 3; jM < fimJ; jM ++)
          {
            numeros[sudoku[iM][jM]] ++;
          }
        }

        int unik = 0, onlyToFit;
        for (iM = 1; iM < 10; iM ++) //Verifica qual número falta
        {
          if (numeros[iM] == 0)
          {
            unik ++;
            onlyToFit = iM;
          }
        }
        if (unik == 1)
        {
          sudoku[i][j] = onlyToFit; //Insere o número que falta
          solve(); //Recomeça
        }
      }
    }
  }
  return;
}

int main()
{
  int tests; scanf("%d", &tests);
  int li, lj; int num;
  while (tests -- > 0)
  {
    for (li = 0; li < 9; li ++)
    {
      getchar();
      for (lj = 0; lj < 9; lj ++)
      {
        scanf("%01d", &sudoku[li][lj]);
      }
    }
    solve();
    printar();
  }
  return(0);
}
