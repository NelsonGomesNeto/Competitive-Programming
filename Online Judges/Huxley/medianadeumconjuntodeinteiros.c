#include <stdio.h>

float num[999]; int repeat = 1;

int ordem()
{
  int bubble, orga; float aux;
  for (bubble = 0; bubble < repeat; bubble ++)
  {
    for(orga = 1; orga < repeat; orga ++)
    {
      if (num[bubble] > num[orga])
      {
        aux = num[bubble];
        num[bubble] = num[orga];
        num[orga] = aux;
      }
    }
  }
}

int main()
{
  while (scanf("%f", &num[repeat]) != EOF)
  {
    repeat ++;
  }
  ordem();
  if ((repeat - 1) % 2 == 0)
  {
    printf("Mediana = %.1f\n", (float) (num[repeat/2] + num[(repeat/2) + 1]) / 2);
  }
  else
  {
    printf("Mediana = %d\n", (int) num[repeat/2]);
  }
  return(0);
}
