#include <stdio.h>
#include <math.h>

void swap(int *a, int *b)
{
  int aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

int main()
{
  int numeros;
  while (scanf("%d", &numeros) && numeros != 0)
  {
    int ler, array[numeros], win = 0;
    for (ler = 0; ler < numeros; ler ++)
    {
      scanf("%d", &array[ler]);
    }
    int i;
    int aux;
    for (i = 0; i < numeros; i ++)
    {
      if (array[i] - 1 != i)
      {
        win += (2 * ((array[i] - 1) - i)) - 1;
        swap(&array[i], &array[array[i] - 1]);
        i --;
      }
    }
    printf("%d\n", win);
    if (win % 2 != 0)
    {
      printf("Marcelo\n");
    }
    else
    {
      printf("Carlos\n");
    }
  }
  return(0);
}
