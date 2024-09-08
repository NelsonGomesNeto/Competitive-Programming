#include <stdio.h>

int main()
{
  double notaA, notaB, notaC, media;
  scanf("%lf\n%lf\n%lf", &notaA, &notaB, &notaC);
  media = ((notaA * 2) + (notaB * 3) + (notaC * 5))/10;
  printf("MEDIA = %.1lf\n", media);
  return(0);
}
