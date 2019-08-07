#include <stdio.h>

void printPar(int num, int start)
{
  if (start <= num)
  {
    if (start % 2 == 0)
    {
      printf("%d\n", start);
    }
    printPar(num, start + 1);
  }
}

int main()
{
  int N; scanf("%d", &N);
  printPar(N, 0);
  return(0);
}
