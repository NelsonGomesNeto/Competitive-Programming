#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int array[tam], ler, change, aux[tam], posi;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &array[ler]);
    aux[ler] = array[ler];
  }
  int vez;
  scanf("%d", &vez);
  for (change = 0; change < tam; change ++)
  {
    posi = change + vez;
    posi = posi % tam;
    array[change] = aux[posi];
  }
  for (ler = 0; ler < tam; ler ++)
  {
    printf("%d\n", array[ler]);
  }
  return(0);
}
