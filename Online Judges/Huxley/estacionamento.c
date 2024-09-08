#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tam, jump;

int goes(int gar[], int ID, int carro, int i)
{
  int aux = carro;
  while (i < tam && gar[i] == 0 && carro > 0)
  {
    gar[i] = ID;
    carro --; i ++;
  }
  if (carro == 0)
  {
    return(1);
  }
  else
  {
    jump = aux - carro;
    while (carro < aux)
    {
      carro ++; i --;
      gar[i] = 0;
    }
  }
  return(0);
}

int tryPut(int garagem[], int ID, int carro)
{
  int j;
  for (j = 0; j < tam; j ++)
  {
    if (garagem[j] == 0)
    {
      if (goes(garagem, ID, carro, j))
      {
        return(j);
      }
      j += jump;
    }
  }
  return(-1);
}

void remov(int garagem[], int start, int ID)
{
  int i = start;
  while (i < tam && garagem[i] == ID)
  {
    garagem[i] = 0; i ++;
  }
  return;
}

void printar(int array[])
{
  int i;
  for (i = 0; i < tam; i ++)
  {
    printf("%d ", array[i]);
  } printf("\n");
}

int main()
{
  int acoes; char oper;
  while (scanf("%d %d", &tam, &acoes) && !(tam == -1 && acoes == -1))
  {
    int *park = calloc(tam, sizeof(int)), placa, size;
    int i;
    int posicoes[10000];
    double lucro = 0;
    while (acoes > 0)
    {
      //printar(park);
      getchar();
      scanf("%c", &oper);
      if (oper == 'C')
      {
        scanf("%d %d", &placa, &size);
        int tryHard = tryPut(park, placa, size);
        if (tryHard != -1)
        {
          posicoes[placa] = tryHard;
          lucro += 10;
        }
      }
      else
      {
        scanf("%d", &placa);
        remov(park, posicoes[placa], placa);
      }
      acoes --;
    }
    free(park);
    printf("%.0lf\n", lucro);
  }
  return(0);
}
