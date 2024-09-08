#include <stdio.h>

int main()
{
  int N, test, naoprimo;
  while (scanf("%d", &N) && N != 0)
  {
    naoprimo = 1;
    test = 1;
    while (test < N)
    {
      naoprimo = 0;
      if (N % test == 0 && test > 1 && test < (N / 2) + 1)
      {
        //printf("Não é primo, é divisivel por: %d\n", test);
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
