#include <stdio.h>

int bubble, ordem; double lado[3], aux;

int orga()
{
  for (ordem = 0; ordem < 3; ordem ++)
  {
    for (bubble = 0; bubble < 3; bubble ++)
    {
      if (lado[ordem] < lado[bubble])
      {
        aux = lado[bubble];
        lado[bubble] = lado[ordem];
        lado[ordem] = aux;
      }
    }
  }
}

int main()
{
  int repeat;
  for (repeat = 0; repeat < 3; repeat ++)
  {
    scanf("%lf", &lado[repeat]);
  }
  orga();
  if (lado[2] < lado[1] + lado[0] && lado[2] > lado[1] - lado[0])
  {
    if (lado[0] == lado[1] && lado[1] == lado[2])
    {
      printf("EQUILATERO\n");
    }
    else if ((lado[0] == lado[1]) || (lado[0] == lado[2]) || (lado[1] == lado[2]))
    {
      printf("ISOSCELES\n");
    }
    else
    {
      printf("ESCALENO\n");
    }
  }
  else
  {
    printf("-\n");
  }
  return(0);
}
