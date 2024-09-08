#include <stdio.h>

int main()
{
  double num, media = 0; int i;
  for (i = 0; i < 100; i ++)
  {
    printf("Digite um numero:\n");
    scanf("%lf", &num);
    media += num;
  }
  media /= 100;
  printf("Media dos numeros: %.15lf\n", media);
  return(0);
}
