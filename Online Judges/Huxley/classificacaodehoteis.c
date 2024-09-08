#include <stdio.h>
#include <string.h>

int main()
{
  int repeat, convert, star, mediaCG = 0, diviCG = 0, quantRT = 0, bestJP = 0;
  char tipo[20], city[20];
  for (repeat = 0; repeat < 10; repeat ++)
  {
    scanf("%s\n%i", &*tipo, &star);
    getchar();
    scanf("%[^\n]", &*city);
    for (convert = 0; convert < 20; convert ++)
    {
      tipo[convert] = tolower(tipo[convert]);
      city[convert] = tolower(city[convert]);
    }
    if (strcmp(city,"campina grande") == 0)
    {
      mediaCG += star;
      diviCG ++;
    }
    else if (strcmp(city,"rio tinto") == 0)
    {
      if (strcmp(tipo,"pousada") == 0)
      {
        quantRT ++;
      }
    }
    else if (strcmp(city,"joao pessoa") == 0 || strcmp(city,"joão pessoa") == 0 || strcmp(city,"joÃo pessoa") == 0)
    {
      if (strcmp(tipo,"hotel") == 0 && star == 5)
      {
        bestJP ++;
      }
    }
  }
  if (diviCG > 0)
  {
    mediaCG /= diviCG;
  }
  printf("%i\n%i\n%i\n", bestJP, mediaCG, quantRT);
  return(0);
}
