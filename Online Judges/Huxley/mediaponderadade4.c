#include <stdio.h>

float nota1, nota2, nota3, nota4;

float AnalisarSituacao(float nota1, float nota2, float nota3, float nota4)
{
  float media = (nota1 + nota2 * 2 + nota3 * 3 + nota4 * 4) / 10;
  if (media >= 9)
  {
    printf("aprovado com louvor\n");
  }
  else if (media >= 7)
  {
    printf("aprovado\n" );
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

int main()
{
  scanf("%f %f %f %f", &nota1, &nota2, &nota3, &nota4);
  AnalisarSituacao(nota1, nota2, nota3, nota4);
  return(0);
}
