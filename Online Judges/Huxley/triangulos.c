#include <stdio.h>
#include <math.h>

int bubble, ordem; double PI = 3.14159265, lado[3], aux;

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
  scanf("%lf %lf %lf", &lado[0], &lado[1], &lado[2]);
  orga();
  /*if (acos(lado[0]/lado[2]) > PI / 2
  ||  acos(lado[1]/lado[2]) > PI / 2)*/
  if (lado[2] < lado[1] + lado[0] && lado[2] > lado[1] - lado[0])
  {
    if (pow(lado[2],2) > pow(lado[1],2) + pow(lado[0],2))
    {
      printf("o\n");
    }
    else if (pow(lado[2],2) == pow(lado[1],2) + pow(lado[0],2))
    {
      printf("r\n");
    }
    /*else if (acos(lado[0]/lado[2]) < PI / 2
          && acos(lado[1]/lado[2]) < PI / 2)*/
    else //(pow(lado[2],2) < pow(lado[1],2) + pow(lado[0],2))
    {
      printf("a\n");
    }
  }
  else
  {
    printf("n\n");
  }
  return(0);
}
