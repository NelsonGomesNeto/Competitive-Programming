#include <stdio.h>

int main()
{
  int M, N, maior = 0;
  scanf("%i\n%i", &M, &N);
  while (N > M)
  {
    if (N % M == 0 && N > maior)
    {
      maior = N;
    }
    N --;
  }
  if (maior == 0)
  {
    printf("sem multiplos menores que %i\n", N);
  }
  else
  {
    printf("%i\n", maior);
  }
  return(0);
}
