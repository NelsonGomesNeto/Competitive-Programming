#include <stdio.h>

int main()
{
  int tam, i; scanf("%d", &tam);
  int array, soma = 0;
  for (i = 0; i < tam; i ++)
  {
    scanf("%d", &array);
    if (array & 1) //impar
    {
      soma -= 1;
    }
    else
    {
      soma += 1;
    }
  }
  printf("%d\n", soma);
  return(0);
}
