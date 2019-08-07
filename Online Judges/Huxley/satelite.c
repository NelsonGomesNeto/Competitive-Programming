#include <stdio.h>
#include <stdlib.h>

char mat[300][300]; int posI, posJ;

void sat(int i, int fimI, int j, int fimJ)
{
  int meioI = (i + fimI) / 2;
  int meioJ = (j + fimJ) / 2;
  if (i - meioI == 0 && j - meioJ == 0)
  {
    return;
  }
  if (posI < meioI && posJ >= meioJ)
  {
    printf("1");
    sat(i, meioI, meioJ, fimJ);
  }
  else if (posI < meioI && posJ < meioJ)
  {
    printf("2");
    sat(i, meioI, j, meioJ);
  }
  else if (posI >= meioI && posJ < meioJ)
  {
    printf("3");
    sat(meioI, fimJ, j, meioJ);
  }
  else if (posI >= meioI && posJ >= meioJ)
  {
    printf("4");
    sat(meioI, fimI, meioJ, fimJ);
  }
}

int main()
{
  int tam; scanf("%d", &tam);
  int ler;
  for (ler = 0; ler < tam; ler ++)
  {
    getchar();
    scanf("%s", mat[ler]);
  }
  int i, j;
  for (i = 0; i < tam; i ++)
  {
    for (j = 0; j < tam; j ++)
    {
      if (mat[i][j] == '*')
      {
        posI = i; posJ = j;
      }
    }
  }
  sat(0, tam, 0, tam);
  printf("0\n");
  return(0);
}
