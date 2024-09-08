#include <stdio.h>

int main()
{
  char gabarito[10] = "ABCDEEDCBA", ans;
  int questao = 1, nota = 0;
  while (questao < 11)
  {
    printf("Insira a resposta do aluno para a pergunta %d:\n", questao);
    scanf("%c", &ans);
    getchar();
    if (ans == gabarito[questao - 1])
    {
      nota ++;
    }
    questao ++;
  }
  printf("Nota do aluno: %d\n", nota);
  return(0);
}
