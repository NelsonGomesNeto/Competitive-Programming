#include <stdio.h>
#include <math.h>
#include <string.h>

#define lol 999

int matriz[lol][lol], j, i, Ymax, Xmax, col = 0;
char ans[999999], an = 0;

int check(int y, int x, int Yf, int Xf, int COL)
{
  int jM, iM, nope = 0, num = 0, checked = 0;
  //printf("~~~~~~~~~~%dx%d||%dx%d\n", y, x, Yf, Xf);
  num = matriz[Yf][Xf];
  for (jM = y; jM <= Yf; jM ++)
  {
    for (iM = x; iM <= Xf; iM ++)
    {
      if (iM < Ymax && jM < Xmax)
      {
        //printf("%d", matriz[jM][iM]);
        if (num != matriz[jM][iM] && (num == 0 || num == 1) && (matriz[jM][iM] == 0 || matriz[jM][iM] == 1))
        {
          nope ++;
        }
      }
      checked ++;
    }
    //printf("\n");
  }
  if (nope != 0)
  {
    /*printf("D");
    if (COL == 51);
    {
      COL = 0;
      printf("\n");
    }*/
    ans[an] = 'D';
    an ++;
    //Yf = (Yf + y) / 2;
    //Xf = (Xf + x) / 2;
    check(y, x, (Yf + y) / 2, (Xf + x) / 2, COL + 1);
    check(y, ((Xf + x) / 2) + 1, (Yf + y) / 2, Xf, COL + 1);
    check(((Yf + y) / 2) + 1, x, Yf, (Xf + x) / 2, COL + 1);
    check(((Yf + y) / 2) + 1, ((Xf + x) / 2) + 1, Yf, Xf, COL + 1);
  }
  else if (checked != 0)
  {
    /*printf("%d", num);
    if (COL == 51);
    {
      COL = 0;
      printf("\n");
    }*/
    ans[an] = num + 48;
    an ++;
  }
  //return(0);
}

int main()
{
int testes; scanf("%d", &testes);
while (testes > 0)
{
  int Y, X; scanf("%d %d", &Y, &X);
  Ymax = Y; Xmax = X;
  char number;
  getchar();
  for (j = 0; j < Y; j ++)
  {
    for (i = 0; i < X; i ++)
    {
      matriz[j][i] = '9';
    }
  }
  for (j = 0; j < Y; j ++)
  {
    for (i = 0; i < X; i ++)
    {
      scanf("%c", &number);
      matriz[j][i] = number - 48;
    }
    getchar();
  }
  col = 0; an = 0;
  for (i = 0; i < 1000000; i ++)
  {
    ans[i] = '\0';
  }
  check(0, 0, Y - 1, X - 1, 0);
  for (i = 0; i < strlen(ans); i ++)
  {
    if (i % 50 == 0 && i > 1)
    {
      printf("\n");
    }
    printf("%c", ans[i]);
  }
  if (i % 50 != 0)
  {
    printf("\n");
  }
  testes --;
}
	return(0);
}
