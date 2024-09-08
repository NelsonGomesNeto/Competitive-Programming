#include <stdio.h>

int main()
{
  float num1, num2, num3, media; int acima = 0;
  scanf("%f\n%f\n%f", &num1, &num2, &num3);
  media = (num1 + num2 + num3) / 3;
  if (num1 < media) { acima ++; }
  if (num2 < media) { acima ++; }
  if (num3 < media) { acima ++; }
  printf("%d\n", acima);
  return(0);
}
