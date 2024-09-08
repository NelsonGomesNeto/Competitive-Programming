#include <stdio.h>
#include <math.h>

int main()
{
  double num;
  scanf("%lf", &num);
  if (num > 0)
  {
    if (round(num / 2) - (num / 2) == 0)
    {
      printf("POSITIVO PAR\n");
    }
    else
    {
      printf("POSITIVO IMPAR\n");
    }
  }
  else if (num < 0)
  {
    if (round(num / 2) - (num / 2) == 0)
    {
      printf("NEGATIVO PAR\n");
    }
    else
    {
      printf("NEGATIVO IMPAR\n");
    }
  }
  else
  {
    printf("NULO\n");
  }
  return(0);
}
