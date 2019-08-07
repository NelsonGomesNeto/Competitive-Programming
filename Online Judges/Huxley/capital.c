#include <stdio.h>

int A[4];

int orga()
{
  int ordem, bubble, aux;
  for (ordem = 0; ordem < 4; ordem ++)
  {
    for (bubble = 0; bubble < 4; bubble ++)
    {
      if (A[ordem] < A[bubble])
      {
        aux = A[bubble];
        A[bubble] = A[ordem];
        A[ordem] = aux;
      }
    }
  }
}

int main()
{
  scanf("%d\n%d\n%d\n%d", &A[0], &A[1], &A[2], &A[3]);
  orga();
  if (A[0] * A[3] == A[1] * A[2])
  {
    printf("S\n");
  }
  else
  {
    printf("N\n");
  }
  return(0);
}
