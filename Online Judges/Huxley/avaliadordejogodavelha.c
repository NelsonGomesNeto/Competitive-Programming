#include <stdio.h>
#include <string.h>

void check(char m[][3], char oper, int *w)
{
  //Diagonais
  if (m[0][0] == oper && m[1][1] == oper && m[2][2] == oper)
  {
    (*w) ++;
  }
  if (m[0][2] == oper && m[1][1] == oper && m[2][0] == oper)
  {
    (*w) ++;
  }
  //Linhas
  if (m[0][0] == oper && m[0][1] == oper && m[0][2] == oper)
  {
    (*w) ++;
  }
  if (m[1][0] == oper && m[1][1] == oper && m[1][2] == oper)
  {
    (*w) ++;
  }
  if (m[2][0] == oper && m[2][1] == oper && m[2][2] == oper)
  {
    (*w) ++;
  }
  //Colunas
  if (m[0][0] == oper && m[1][0] == oper && m[2][0] == oper)
  {
    (*w) ++;
  }
  if (m[0][1] == oper && m[1][1] == oper && m[2][1] == oper)
  {
    (*w) ++;
  }
  if (m[0][2] == oper && m[1][2] == oper && m[2][2] == oper)
  {
    (*w) ++;
  }
}

int main()
{
  int jogos, run = 0; scanf("%d", &jogos);
  getchar();
  while (jogos > 0)
  {
    char campo[3][3];
    int j, i, X = 0, O = 0;
    for (j = 0; j < 3; j ++)
    {
      for (i = 0; i < 3; i ++)
      {
        scanf("%c", &campo[j][i]);
        getchar();
        if (campo[j][i] == 'X')
        {
          X ++;
        }
        else if (campo[j][i] == 'O')
        {
          O ++;
        }
      }
    }
    int winX = 0, winO = 0;
    check(campo, 'X', &winX);
    check(campo, 'O', &winO);
    if (winX >= 1 && winO == 0 && X - O == 1)
    {
      printf("X_VENCEU\n");
    }
    else if (winO >= 1 && winX == 0 && X - O == 0)
    {
      printf("O_VENCEU\n");
    }
    else if (winO == 0 && winX == 0)//if (X - O > 1 || X - O < 0 || (winX >= 1 && winO >= 1) || X > 5 || O > 4)
    {
      printf("EM_ANDAMENTO\n");
    }
    else
    {
      printf("ILEGAL\n");
    }
    jogos --;
  }
  return(0);
}
