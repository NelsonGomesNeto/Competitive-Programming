#include <stdio.h>

int main()
{
  int gol, golC = 0, golEd = 0, repeat, desempate = 0;
  for (repeat = 0; repeat < 10; repeat ++)
  {
    scanf("%i", &gol);
    if (repeat == 0 || repeat % 2 == 0)
    {
      golC += gol;
    }
    else
    {
      golEd += gol;
    }
    if (repeat > 7 && golEd - golC >= 3)
    {
      printf("EDUCACAO FISICA\n");
      return(0);
    }
    if (repeat > 7 && golC - golEd >= 3)
    {
      printf("COMPUTACAO.RAR\n");
      return(0);
    }
  }
  if (golC > golEd)
  {
    printf("COMPUTACAO.RAR\n");
  }
  else if (golEd < golC)
  {
    printf("EDUCACAO FISICA\n");
  }
  else
  {
    while (desempate == 0)
    {
      scanf("%i\n%i", &golC, &golEd);
      desempate = golC - golEd;
    }
    if (golC > golEd)
    {
      printf("COMPUTACAO.RAR\n");
    }
    else if (golEd > golC)
    {
      printf("EDUCACAO FISICA\n");
    }
  }
}
