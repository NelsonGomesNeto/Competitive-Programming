#include <stdio.h>

int main()
{
  int baseMenor, baseMaior, altura;
  scanf("%d\n%d\n%d", &baseMenor, &baseMaior, &altura);

  printf("%.1lf\n", (double) ((baseMenor + baseMaior) * altura)/2);

  return(0);
}
