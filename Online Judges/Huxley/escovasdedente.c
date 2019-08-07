#include <stdio.h>

int main()
{
  int alunos;
  float preco;
  scanf("%i", &alunos);
  preco = (2.2 * alunos) - ((alunos / 3) * 2.2);
  printf("%.2f\n", preco);
  return(0);
}
