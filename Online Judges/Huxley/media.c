#include <stdio.h>

int main()
{
  double notaA, notaB, media;
  scanf("%lf\n%lf", &notaA, &notaB);
  media = ((notaA * 3.5) + (notaB * 7.5))/11;
  printf("MEDIA = %.5lf\n", media);
  return(0);
}
