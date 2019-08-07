#include <stdio.h>
#include <stdlib.h>

void findHam(int tam, int i, int toHam, int string[])
{
  if (i == tam)
  {
    int k, conta = 0;
    for (k = 0; k < tam; k ++)
    {
      if (string[k] == 1)
      {
        conta ++;
      }
    }
    if (conta == toHam)
    {
      for (k = 0; k < tam; k ++)
      {
        printf("%d", string[k]);
      } printf("\n");
    }
    return;
  }
  int j;
  for (j = 0; j < 2; j ++)
  {
    string[i] = j;
    findHam(tam, i + 1, toHam, string);
  }
}

int main()
{
  int testes, run = 0; scanf("%d", &testes);
  while (testes > 0)
  {
    if (run > 0)
    {
      printf("\n");
    }
    run ++;
    int tamanho, ham; scanf("%d %d", &tamanho, &ham);
    int string[tamanho];
    findHam(tamanho, 0, ham, string);
    testes --;
  }
  return(0);
}
