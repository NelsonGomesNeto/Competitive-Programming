#include <stdio.h>
#include <string.h>

int main()
{
  char voto[10];
  int convert, sim = 0, nao = 0;
  do
  {
    scanf("%s", &*voto);
    for (convert = 0; convert <= 10; convert ++)
    {
      voto[convert] = tolower(voto[convert]);
    }
    if (strcmp(voto,"sim") == 0)
    {
      sim ++;
    }
    else { nao ++; }
  } while (strcmp(voto,"encerrar") != 0);
  nao --;
  if (sim > nao)
  {
    printf("COM FOGOS\n");
  }
  else
  {
    printf("SEM FOGOS\n");
  }
  return(0);
}
