#include <stdio.h>

int main()
{
  float nota, media = 0;
  printf("Informe a primeira nota do aluno:\n");
  scanf("%f", &nota); media += nota;
  printf("Informe a segunda nota do aluno:\n");
  scanf("%f", &nota); media += nota;
  printf("Informe a terceira nota do aluno:\n");
  scanf("%f", &nota); media += nota;
  printf("Informe a quarta nota do aluno:\n");
  scanf("%f", &nota); media += nota;
  printf("Media: %.3f\n", media / 4);
  return(0);
}
