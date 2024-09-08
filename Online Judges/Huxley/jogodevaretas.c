#include <stdio.h>

int main()
{
  int conjuntos;
  while (scanf("%d", &conjuntos) && conjuntos != 0)
  {
    int i, tam, quanti, pares = 0;
    for (i = 0; i < conjuntos; i ++)
    {
      scanf("%d %d", &tam, &quanti);
      pares += (quanti / 2);
    }
    
    int retangulos = pares / 2;
    printf("%d\n", retangulos);
  }
  return(0);
}
