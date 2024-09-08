#include <stdio.h>

int main()
{
  int angulo;
  while (scanf("%d", &angulo) && angulo != -1)
  {
    if (angulo % 6 == 0)
    {
      printf("Y\n");
    }
    else
    {
      printf("N\n");
    }
  }
  return(0);
}
