#include <stdio.h>
#include <stdlib.h>
int main()
{
  int tam;
  int dif[9999];
  while (scanf("%d", &tam) != EOF)
  {
    int array[9999], i;
    for (i = 0; i < tam; i ++)
    {
      scanf("%d", &array[i]);
    }
    for (i = 0; i < tam - 1; i ++)
    {
      dif[i] = abs(array[i] - array[i + 1]);
    }
    int o, b, aux;
    for (o = 0; o < tam - 1; o ++)
    {
      for (b = o; b < tam - 1; b ++)
      {
        if (dif[o] > dif[b])
        {
          aux = dif[o];
          dif[o] = dif[b];
          dif[b] = aux;
        }
      }
    }
    int jolly = 1; aux = dif[0];
    for (i = 1; i < tam - 1; i ++)
    {
      //printf("%d\n", dif[i]);
      if (dif[i] - aux != 1)
      {
        jolly = 0;
      }
      aux = dif[i];
    }
    if (jolly == 1)
    {
      printf("Jolly\n");
    }
    else
    {
      printf("Not jolly\n");
    }
  }
  return(0);
}
