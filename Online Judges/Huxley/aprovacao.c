#include <stdio.h>

int main()
{
  long double nota, media = 0;
  printf("Informe a primeira nota:\n");
  scanf("%Lf", &nota); media += nota;
  printf("Informe a segunda nota:\n");
  scanf("%Lf", &nota); media += nota;
  printf("Informe a terceira nota:\n");
  scanf("%Lf", &nota); media += nota;
  media /= 3;
  if (media < 5)
  {
    printf("Reprovado com media ");
  }
  else if (media < 7)
  {
    printf("Recuperacao com media ");
  }
  else
  {
    printf("Aprovado com media ");
  }
  if (media - (int)media == 0)
  {
    printf("%.1Lf", media);
  }
  else
  {
    printf("%.15Lf", media);
  }
  printf("\n");
  return(0);
}
