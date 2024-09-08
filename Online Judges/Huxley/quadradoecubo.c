#include <stdio.h>

int main()
{
  int N, repeat, quad, cube;
  scanf("%i", &N);
  repeat = N;
  for (N = 1; N <= repeat; N ++)
  {
    quad = N * N; cube = N * N * N;
    printf("%i %i %i\n", N, quad, cube);
  }
  return(0);
}
