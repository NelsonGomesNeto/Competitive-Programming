#include <stdio.h>
#include <string.h>

int main()
{
  int linhas; scanf("%d", &linhas);
  char string[linhas + 1][300], wanted, most[300 * linhas + 1]; int ler, qWanted = 0, qMost = 0;
  for (ler = 0; ler < linhas; ler ++)
  {
    getchar();
    scanf("%[^\n]", string[ler]);
    if (ler == 0)
    {
      strcpy(most, string[ler]);
    }
    else
    {
      strcat(most, string[ler]);
    }
  }
  getchar();
  scanf("%c", &wanted);
  int j, i, iM = 0;
  for (j = 0; j < linhas; j ++)
  {
    for (i = 0; i < strlen(string[j]); i ++)
    {
      if (string[j][i] == wanted)
      {
        qWanted ++;
      }
    }
  }
  int o, b; char aux;
  for (o = 0; o < strlen(most); o ++)
  {
    for (b = o; b < strlen(most); b ++)
    {
      if (most[o] > most[b])
      {
        aux = most[o];
        most[o] = most[b];
        most[b] = aux;
      }
    }
  }
  char oMost; int quanti;
  for (o = 0; o < strlen(most); o ++)
  {
    quanti = 0;
    for (b = 0; b < strlen(most); b ++)
    {
      if (most[o] == most[b])
      {
        quanti ++;
      }
    }
    if (quanti > qMost)
    {
      qMost = quanti;
      oMost = most[o];
    }
  }
  printf("%c %d %d\n", oMost, qMost, qWanted);
  return(0);
}
