#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void completarMultiplos(int a[], long long int num)
{
  int aux = num; num *= num;
  while (num < 1000001)
  {
    a[num] = 0;
    num *= aux;
  }
}

int main()
{
  int tests; scanf("%d", &tests);

  int *primos = malloc(1000001 * sizeof(int));
  memset(primos, -1, 1000001 * sizeof(int));
  primos[1] = 0; primos[2] = 1; primos[3] = 1; primos[1000000] = 0;
  completarMultiplos(primos, 2); completarMultiplos(primos, 3);

  int *respostas = malloc(1000001 * sizeof(int));
  respostas[1] = 0; respostas[2] = 1; respostas[3] = 2; respostas[1000000] = 78498;

  int fill, conta = 2;
  for (fill = 5; fill < 1000001; fill += 2)
  {
    primos[fill - 1] = 0;
    if (primos[fill] == -1)
    {
      int is = 1, divi, raiz = sqrt(fill);
      for (divi = 2; divi <= raiz; divi ++)
      {
        if (fill % divi == 0)
        {
          is = 0; primos[fill] = 0;
          break;
        }
      }
      if (is == 1)
      {
        primos[fill] = 1;
        completarMultiplos(primos, (long long int) fill);
      }
    }
    respostas[fill - 1] = conta;
    conta += primos[fill];
    respostas[fill] = conta;
  }

  while (tests > 0)
  {
    long int from, to, quanti;
    scanf("%ld %ld", &from, &to);
    if (from > to)
    {
      printf("-1\n"); tests --; continue;
    }
    if (from == to)
    {
      if ( (double) sqrt(from) == (int) (sqrt(from)) )
      {
        quanti = primos[(int) sqrt(from)];
      }
      else
      {
        quanti = 0;
      }
    }
    else
    {
      from = ceil(sqrt(from)) - 1; to = floor(sqrt(to));
      if (from < 1) { from = 1; }
      if (from != to)
      {
        quanti = respostas[to] - respostas[from];
      }
    }
    printf("%ld\n", quanti);
    tests --;
  }

  free(primos);
  free(respostas);
  return(0);
}
