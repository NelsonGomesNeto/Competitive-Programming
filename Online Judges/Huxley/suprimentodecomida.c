#include <stdio.h>

int main()
{
  int N, dias; float food;
  scanf("%i", &N);
  while (N > 0)
  {
    dias = 0;
    scanf("%f", &food);
    while (food >= 1)
    {
      food /= 2;
      dias ++;
    }
    printf("%i dias\n", dias);
    N --;
  }
  return(0);
}
