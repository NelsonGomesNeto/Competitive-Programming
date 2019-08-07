#include <stdio.h>

int main()
{
  int tam, lerX = 0, lerY = 0, n, fim = 0, par = 0; scanf("%d", &tam);
  int matriz[tam][tam];
  n = tam; int print = tam;
  if (tam > 1)
  {
    while (n > 0)
    {
      if (par == 1)
      {
        par --;
        tam --;
        for (lerY = tam - 1; lerY >= fim; lerY --)
        {
          scanf("%d", &matriz[lerX][lerY]);
        }
        lerY ++;
        fim ++;
        for (lerX = tam - 1; lerX >= fim; lerX --)
        {
          scanf("%d", &matriz[lerX][lerY]);
        }
        lerX ++;
      }
      else
      {
        par ++;
        for (lerY = fim; lerY < tam; lerY ++)
        {
          scanf("%d", &matriz[lerX][lerY]);
        }
        lerY --;
        for (lerX = fim + 1; lerX < tam; lerX ++)
        {
          scanf("%d", &matriz[lerX][lerY]);
        }
        lerX --;
        //fim ++;
      }
      n --;
    }
    for (lerX = 0; lerX < print; lerX ++)
    {
      for (lerY = 0; lerY < print; lerY ++)
      {
        printf("%d\n", matriz[lerY][lerX]);
      }
    }
  }
  else if (tam == 1)
  {
    scanf("%d", &fim);
    printf("%d\n", fim);
  }
  //printf("~~~~~~\n");
  return(0);
}
