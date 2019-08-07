#include <stdio.h>

int main()
{
  int num[999], repeat = 0, check, todos, conta = 0, moda = 0, numModa;
  while (scanf("%d", &num[repeat]) != EOF)
  {
    repeat ++;
  }
  for (check = 0; check < repeat; check ++)
  {
    conta = 0;
    for (todos = 0; todos < repeat; todos ++)
    {
      if (num[check] == num[todos])
      {
        conta ++;
      }
    }
    if (conta > moda)
    {
      numModa = num[check];
      moda = conta;
    }
  }
  printf("Moda = %d\n", numModa);
  return(0);
}
