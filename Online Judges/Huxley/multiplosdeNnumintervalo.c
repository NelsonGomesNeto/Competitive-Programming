#include <stdio.h>

int main()
{
  int N, A, B, existe = 0;
  scanf("%i\n%i\n%i", &N, &A, &B);
  while (A <= B)
  {
    if (A % N == 0)
    {
      printf("%i\n", A);
      existe ++;
    }
    A ++;
  }
  if (existe == 0)
  {
    printf("INEXISTENTE\n");
  }
  return(0);
}
