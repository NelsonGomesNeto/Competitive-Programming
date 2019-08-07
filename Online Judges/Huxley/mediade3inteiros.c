#include <stdio.h>

int main()
{
  double num[3], media;
  scanf("%lf\n%lf\n%lf", &num[0], &num[1], &num[2]);
  media = (num[0] + num[1] + num[2]) / 3;
  printf("%.2le\n", media);
  return(0);
}
