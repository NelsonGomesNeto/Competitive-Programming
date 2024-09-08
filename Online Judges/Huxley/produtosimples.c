#include <stdio.h>

int main()
{
  int num, prod = 1;
  while (scanf("%d", &num) != EOF)
  {
    prod *= num;
  }
  printf("Prod = %d\n", prod);
  return(0);
}
