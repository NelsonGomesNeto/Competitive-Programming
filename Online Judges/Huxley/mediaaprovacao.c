#include <stdio.h>

int main()
{
  double notaA, notaB, notaC, media;
  scanf("%lf\n%lf\n%lf", &notaA, &notaB, &notaC);
  media = (notaA + notaB + notaC)/3;
  if (media >= 7)
  {
    printf("aprovado\n");
  }
  else if (media < 3)
  {
    printf("reprovado\n");
  }
  else
  {
    printf("prova final\n");
  }
  return(0);
}
