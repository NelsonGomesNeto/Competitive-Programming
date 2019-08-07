#include <stdio.h>

int main()
{
  long int N, test, naoprimo;
  while (scanf("%ld", &N) && N != -1)
  {
    naoprimo = 1;
    test = 1;
    while (test < N)
    {
      naoprimo = 0;
      if (N % test == 0 && test > 1)
      {
        naoprimo ++;
        break;
      }
      test ++;
    }
    if (naoprimo > 0)
    {
      printf("0\n");
    }
    else
    {
      printf("1\n");
    }
  }
  return(0);
}
