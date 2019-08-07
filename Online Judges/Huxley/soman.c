#include <stdio.h>

int main()
{
  int repeat, nvezes, number, result = 0;
  scanf("%d", &nvezes);
  for (repeat = 0; repeat < nvezes; repeat++)
  {
    scanf("%d", &number);
    result = result + number;
  }
  printf("%d\n", result);
  return(0);
}
