#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
  int tests; scanf("%d", &tests);
  int *primos = malloc(1000001 * sizeof(int)), prevSize = 3;
  memset(primos, -1, 1000001 * sizeof(int));
  primos[0] = 0; primos[1] = 0; primos[2] = 1;
  int *respostas = malloc(1000001 * sizeof(int));
  memset(respostas, -1, 1000001 * sizeof(int));
  while (tests > 0)
  {
    long int from, to, conta = 0;
    scanf("%ld %ld", &from, &to);
    long int perfeito = ceil(sqrt(from)), fim = floor(sqrt(to));
    for (; perfeito <= fim; perfeito ++)
    {
      if (respostas[perfeito] != -1 && respostas[fim] != -1 && fim != perfeito)
      {
        conta += respostas[fim] - respostas[perfeito];
        break;
      }
      if (primos[perfeito] == -1)
      {
        if (perfeito & 1)
        {
          int is = 1, divi, raiz = sqrt(perfeito);
          for (divi = 2; divi <= raiz; divi ++)
          {
            if (perfeito % divi == 0)
            {
              is = 0; primos[perfeito] = 0;
              break;
            }
          }
          if (is == 1) { primos[perfeito] = 1; }
        }
        else { primos[perfeito] = 0; }
      }
      conta += primos[perfeito];
      respostas[perfeito] = conta;
    }
    printf("%ld\n", conta);
    tests --;
  }
  free(primos);
  free(respostas);
  return(0);
}
