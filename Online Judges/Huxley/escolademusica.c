#include <stdio.h>

char *ClassificaAluno(float nota,int faltas)
{
  if (faltas > 10)
  {
    return("REPROVADO POR FALTAS");
  }
  else if (nota < 7)
  {
    return("REPROVADO");
  }
  else if (nota < 9.5)
  {
    return("APROVADO");
  }
  else
  {
    return("APROVADO COM LOUVOR");
  }
}

int main()
{
  float nota; int faltas;
  scanf("%f\n%i", &nota, &faltas);
  printf("%s\n", &*ClassificaAluno(nota, faltas));
  return(0);
}
