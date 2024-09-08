#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void full(char m[][3], char cor)
{
  int jM, iM;
  for (jM = 0; jM < 3; jM ++)
  {
    for (iM = 0; iM < 3; iM ++)
    {
      m[jM][iM] = cor;
    }
  }
}

void swapH(char *a, char *b, char *c, char *d)
{
  char aux1, aux2, aux3, aux4;
  aux1 = *a; aux2 = *b;
  aux3 = *c; aux4 = *d;
  *b = aux1; *c = aux2;
  *d = aux3; *a = aux4;
}

void swap_H(char *a, char *b, char *c, char *d)
{
  char aux1, aux2, aux3, aux4;
  aux1 = *a; aux2 = *b;
  aux3 = *c; aux4 = *d;
  *a = aux2; *c = aux4;
  *d = aux1; *b = aux3;
}

int check(char a[][3], char b[][3], char c[][3], char d[][3], char e[][3], char f[][3])
{
  int j, i;
  for (j = 0; j < 3; j ++)
  {
    for (i = 0; i < 3; i ++)
    {
      //printf("%c ", e[j][i]);
      if (a[j][i] != a[1][1] || b[j][i] != b[1][1] || c[j][i] != c[1][1]
      || d[j][i] != d[1][1] || e[j][i] != e[1][1] || f[j][i] != f[1][1])
      {
        return(0);
      }
    }
    //printf("\n");
  }
  return(1);
}

int main()
{
  char move[99];
  while (scanf("%s", move) != EOF)
  {
    char blue[3][3], green[3][3], red[3][3], orange[3][3], yellow[3][3], white[3][3];
    full(blue, 'B'); full(green, 'G'); full(red, 'R'); full(orange, 'O');
    full(yellow, 'Y'); full(white, 'W');
    int i, j, jC, movements = 0;
    do
    {
      //printf("~~~~~~~~~~~~~~~~\n");
      for (i = 0; i < strlen(move); i ++)
      {
        if (move[i] == 'R')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swapH(&blue[j][2], &yellow[jC][2], &green[jC][2], &white[j][2]);
          }
          swapH(&red[0][2], &red[2][2], &red[2][0], &red[0][0]);
          swapH(&red[0][1], &red[1][2], &red[2][1], &red[1][0]);
        }
        if (move[i] == 'r')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swap_H(&blue[j][2], &yellow[jC][2], &green[jC][2], &white[j][2]);
          }
          swap_H(&red[0][2], &red[2][2], &red[2][0], &red[0][0]);
          swap_H(&red[0][1], &red[1][2], &red[2][1], &red[1][0]);
        }
        else if (move[i] == 'L')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swap_H(&blue[j][0], &yellow[jC][0], &green[jC][0], &white[j][0]);
          }
          swap_H(&orange[0][2], &orange[2][2], &orange[2][0], &orange[0][0]);
          swap_H(&orange[0][1], &orange[1][2], &orange[2][1], &orange[1][0]);
        }
        else if (move[i] == 'l')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swapH(&blue[j][0], &yellow[jC][0], &green[jC][0], &white[j][0]);
          }
          swapH(&orange[0][2], &orange[2][2], &orange[2][0], &orange[0][0]);
          swapH(&orange[0][1], &orange[1][2], &orange[2][1], &orange[1][0]);
        }
        else if (move[i] == 'U')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swapH(&red[0][j], &white[0][j], &orange[0][jC], &yellow[0][jC]);
          }
          swapH(&blue[0][2], &blue[2][2], &blue[2][0], &blue[0][0]);
          swapH(&blue[0][1], &blue[1][2], &blue[2][1], &blue[1][0]);
        }
        else if (move[i] == 'u')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swap_H(&red[0][j], &white[0][j], &orange[0][jC], &yellow[0][jC]);
          }
          swap_H(&blue[0][2], &blue[2][2], &blue[2][0], &blue[0][0]);
          swap_H(&blue[0][1], &blue[1][2], &blue[2][1], &blue[1][0]);
        }
        else if (move[i] == 'D')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swap_H(&red[2][j], &white[2][j], &orange[2][jC], &yellow[2][jC]);
          }
          swap_H(&green[0][2], &green[2][2], &green[2][0], &green[0][0]);
          swap_H(&green[0][1], &green[1][2], &green[2][1], &green[1][0]);
        }
        else if (move[i] == 'd')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swapH(&red[2][j], &white[2][j], &orange[2][jC], &yellow[2][jC]);
          }
          swapH(&green[0][2], &green[2][2], &green[2][0], &green[0][0]);
          swapH(&green[0][1], &green[1][2], &green[2][1], &green[1][0]);
        }
        else if (move[i] == 'F')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swapH(&blue[2][j], &red[j][0], &green[2][jC], &orange[jC][0]);
          }
          swapH(&white[0][2], &white[2][2], &white[2][0], &white[0][0]);
          swapH(&white[0][1], &white[1][2], &white[2][1], &white[1][0]);
        }
        else if (move[i] == 'f')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swap_H(&blue[2][j], &red[j][0], &green[2][jC], &orange[jC][0]);
          }
          swap_H(&white[0][2], &white[2][2], &white[2][0], &white[0][0]);
          swap_H(&white[0][1], &white[1][2], &white[2][1], &white[1][0]);
        }
        else if (move[i] == 'B')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swapH(&blue[0][j], &orange[jC][2], &green[0][jC], &red[j][2]);
          }
          swapH(&yellow[0][2], &yellow[0][0], &yellow[2][0], &yellow[2][2]);
          swapH(&yellow[0][1], &yellow[1][0], &yellow[2][1], &yellow[1][2]);
        }
        else if (move[i] == 'b')
        {
          for (j = 0, jC = 2; j < 3; j ++, jC --)
          {
            swap_H(&blue[0][j], &orange[jC][2], &green[0][jC], &red[j][2]);
          }
          swap_H(&yellow[0][2], &yellow[0][0], &yellow[2][0], &yellow[2][2]);
          swap_H(&yellow[0][1], &yellow[1][0], &yellow[2][1], &yellow[1][2]);
        }
      }
      movements ++;
    } while (check(blue, green, red, orange, yellow, white) == 0);
    printf("%d\n", movements);
    getchar();
  }
  return(0);
}
