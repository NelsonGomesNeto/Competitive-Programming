#include <stdio.h>
#include <string.h>

char city[99], best[99]; int convert;

int check()
{
  scanf("%s", &*city);
  for (convert = 0; convert < 99; convert ++)
  {
    city[convert] = tolower(city[convert]);
  }
  if (strcmp(city,"fim") == 0)
  {
    return(0);
  }
  else
  {
    return(1);
  }
}

int main()
{
  int distancia, longe = 0; float preco;
  while (check() == 1)
  {
    scanf("%i\n%f", &distancia, &preco);
    if (preco * 2 <= 300 && distancia > longe)
    {
      longe = distancia;
      strcpy(best,city);
    }
  }
  for (convert = 0; convert < 99; convert ++)
  {
    best[convert] = toupper(best[convert]);
  }
  if (longe == 0)
  {
    printf("SEM DESTINO\n");
  }
  else
  {
    printf("%s\n", best);
  }
  return(0);
}
