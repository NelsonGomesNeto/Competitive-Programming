#include <stdio.h>

void linha(int tam)
{
  int i;
  for (i = 0; i < tam; i ++)
  {
    printf("*");
  } printf("\n");
}

void meio(int tam)
{
  int i;
  for (i = 0; i < tam; i ++)
  {
    if (i == 0 || i == tam -1)
    {
      printf("*");
    }
    else
    {
      printf(" ");
    }
  } printf("\n");
}


int main()
{
  int tam; scanf("%d", &tam);
  if (tam < 2 || tam > 10)
  {
    printf("Entrada Invalida!\n");
  }
  else
  {
    int i, j;
    for (i = 0; i < tam; i ++)
    {
      if (i == 0 || i == tam - 1)
      {
        linha(tam);
      }
      else
      {
        meio(tam);
      }
    }
  }
  printf("FIM!");
  return(0);
}
