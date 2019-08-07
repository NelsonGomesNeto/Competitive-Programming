#include <stdio.h>

#define read printf("Informe o codigo do aluno: (0 para encerrar o programa)\n")


int main()
{
  int codigo; float n1, n2, n3;
  while (read, scanf("%d", &codigo) && codigo != 0)
  {
    printf("Informe a primeira nota do aluno:\n");
    scanf("%f", &n1);
    printf("Informe a segunda nota do aluno:\n");
    scanf("%f", &n2);
    printf("Informe a terceira nota do aluno:\n");
    scanf("%f", &n3);
    float media = (n1 + n2 + n3) / 3;
    printf("Media do aluno: %g", media);
    if (media - (int) media == 0)
    {
      printf(".0");
    } printf("\n");
  }
  return(0);
}
