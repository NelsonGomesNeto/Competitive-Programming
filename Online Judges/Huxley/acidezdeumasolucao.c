#include <stdio.h>

int main()
{
  double ph; scanf("%lf", &ph);

  if (ph > 7)
    printf("Basica\n");
  else if (ph < 7)
    printf("Acida\n");
  else
    printf("Neutra\n");

  return(0);
}
