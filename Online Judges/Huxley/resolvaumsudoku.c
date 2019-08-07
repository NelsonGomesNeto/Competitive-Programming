#include <stdio.h>
#include <string.h>

int from(int num)
{
  if (num < 3)
  {
    return(0);
  }
  else if (num < 6)
  {
    return(3);
  }
  else
  {
    return(6);
  }
}

int main()
{
  int testes; scanf("%d", &testes);
  int ler, i, j, iM, jM, fromI, fromJ, limI, limJ, zeros = 0, num[9], unik, posi, iT, jT;
  char sudoku[10][10], number;
  while (testes > 0)
  {
    for (ler = 0; ler < 9; ler ++) //Lendo o sudoku
    {
      getchar();
      scanf("%[^\n]", sudoku[ler]);
    }

    for (j = 0; j < 9; j ++) //Checando a quantidade de zeros
    {
      for (i = 0; i < 9; i ++)
      {
        if (sudoku[j][i] == '0')
        {
          zeros ++;
        }
      }
    }
    while (zeros != 0)
    {
      for (j = 0; j < 9; j ++)
      {
        for (i = 0; i < 9; i ++)
        {
          if (sudoku[j][i] == '0') //Começa a procura pelo número
          {
            for (iM = 0; iM < 9; iM ++) //Zera o contador dos números existentes
            {
              num[iM] = 0;
            }
            for (number = '1'; number <= '9'; number ++) //Verifica cada número
            {
              for (jM = 0; jM < 9; jM ++) //Verifica cada coluna
              {
                if (sudoku[jM][i] == number) //Conta cada número
                {
                  num[number - 49] ++;
                }
              }
              for (iM = 0; iM < 9; iM ++) //Verifica cada linha
              {
                if (sudoku[j][iM] == number) //Conta cada número
                {
                  num[number - 49] ++;
                }
              }
              fromI = from(i); //Começo do quadrado
              limI = fromI + 3; //Fim do quadrado
              fromJ = from(j); //Começo do quadrado
              limJ = fromJ + 3; //Fim do quadrado
              for (jM = fromJ; jM < limJ; jM ++) //Verifica cada quadrado
              {
                for (iM = fromI; iM < limI; iM ++)
                {
                  if (sudoku[jM][iM] == number)
                  {
                    num[number - 49] ++;
                  }
                }
              }
            }
            unik = 0;
            for (iM = 0; iM < 9; iM ++) //Verifica se falta apenhas um número
            {
              if (num[iM] == 0) //Verifica se falta apenhas um número
              {
                posi = iM;
                unik ++;
              }
            }
            if (unik == 1) //Se existir apenas um, assume a posição que tem 0 como o valor no sudoku
            {
              sudoku[j][i] = (posi + 1) + 48;
              zeros --;
            }
          }
        }
      }
    }
    for (ler = 0; ler < 9; ler ++)
    {
      printf("%s\n", sudoku[ler]);
    }
    testes --;
  }
}
