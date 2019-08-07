#include <stdio.h>

int main()
{
  int tam, ler; scanf("%d", &tam);
  int arr1[tam], arr2[tam];
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &arr1[ler]);
  }
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &arr2[ler]);
  }
  for (ler = 0; ler < tam; ler ++)
  {
    printf("%d\n%d\n", arr1[ler], arr2[ler]);
  }
  return(0);
}
