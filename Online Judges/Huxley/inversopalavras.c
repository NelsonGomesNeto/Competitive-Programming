#include <stdio.h>

int main()
{
  int repeat, nvezes = 0, nvezesrepeat = 0, inverso;
  do
  {
    char palavraarray[nvezes];
    for (repeat = 0; repeat < nvezes; repeat ++)
    {
      scanf("%c", &palavraarray[repeat]);
    }
    for (inverso = repeat; inverso > 0; inverso --)
    {
      printf("%c", palavraarray[inverso]);
    }
    printf("\n");
    scanf("%i", &nvezes);
  } while (nvezes != 0);
  /*
  for (i = 0; i < nvezes; i++)
  {
    nvezesrepeat += nvezes;
  }
  inverso = nvezesrepeat;
  for (repeat = nvezesrepeat; repeat < nvezesrepeat; repeat++)
  {
    char palavraarray[nvezes];
    inverso += -1;
    printf("%c", palavraarray[inverso]);
  }
  return(0);*/
}
