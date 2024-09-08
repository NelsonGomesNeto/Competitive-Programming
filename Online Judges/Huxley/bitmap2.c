#include <stdio.h>
#include <math.h>
#include <string.h>

int matriz[1000][1000], j, i, Ymax, Xmax, COL = 0;

int check(int y, int x, int Yf, int Xf)
{
	int jM, iM, nope = 0, num = 0, checked = 0;
	num = matriz[y][x];
	for (jM = y; jM <= Yf; jM ++)
	{
		for (iM = x; iM <= Xf; iM ++)
		{
			if (num != matriz[jM][iM])
			{
				nope ++;
			}
			checked ++;
		}
  }
  if (COL == 50)
  {
    COL = 0;
    printf("\n");
  }
  if (nope != 0)
  {
    printf("D");
    COL += 1;
		check(y, x, (Yf + y) / 2, (Xf + x) / 2);
		check(y, ((Xf + x) / 2) + 1, (Yf + y) / 2, Xf);
		check(((Yf + y) / 2) + 1, x, Yf, (Xf + x) / 2);
		check(((Yf + y) / 2) + 1, ((Xf + x) / 2) + 1, Yf, Xf);
  }
  else if (checked != 0)
  {
    printf("%d", num);
    COL += 1;
  }
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
	      scanf("%c", &number);
	      matriz[j][i] = number - 48;
	    }
	    getchar();
	  }
	  COL = 0;
	  check(0, 0, Y - 1, X - 1);
		printf("\n");
	  testes --;
	}
	return(0);
}
