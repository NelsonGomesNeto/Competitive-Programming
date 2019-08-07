#include <stdio.h>

int main()
{
  float nota[3], media = 0; int repeat;
  for (repeat = 0; repeat < 3; repeat ++)
  {
    scanf("%f", &nota[repeat]);
    media += nota[repeat] / 3;
  }
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
