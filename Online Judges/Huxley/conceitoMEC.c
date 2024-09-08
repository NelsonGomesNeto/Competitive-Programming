#include <stdio.h>

int main()
{
  int nlivros, nalunos, conceito;
  scanf("%i\n%i", &nlivros, &nalunos);
  conceito = nalunos / nlivros;
  if (conceito <= 8)
  {
    printf("A\n");
  }
  else if (conceito > 8 && conceito <= 12)
  {
    printf("B\n");
  }
  else if (conceito > 13 && conceito <= 18)
  {
    printf("C\n");
  }
  else
  {
    printf("D\n");
  }
  return(0);
}
