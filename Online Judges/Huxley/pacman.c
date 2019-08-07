#include <stdio.h>
#define save if (comidas >= MEU) { MEU = comidas; }

void colher(int *food, char atual)
{
  if (atual == 'o')
  {
    *food += 1;
  }
  else if (atual == 'A')
  {
    *food = 0;
  }
}

int main()
{
  int tam; scanf("%d", &tam);
  char jogo[tam + 10][tam + 10]; int ler, j, i, comidas = 0, MEU = 0;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%s", jogo[ler]);
  }
  for (j = 0; j < tam; j ++)
  {
    if (j % 2 == 0 || j == 0)
    {
      for (i = 0; i < tam; i ++)
      {
        colher(&comidas, jogo[j][i]);
        save
      }
    }
    else
    {
      for (i = tam - 1; i >= 0; i --)
      {
        colher(&comidas, jogo[j][i]);
        save
      }
    }

  }
  printf("%d\n", MEU);
  return(0);
}
