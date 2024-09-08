#include <stdio.h>

int main()
{
  int questoes, alunos, ler, corrige, nota; scanf("%d", &questoes);
  char gabarito[questoes];
  getchar();
  scanf("%s", gabarito);
  scanf("%d", &alunos);
  for (ler = 0; ler < alunos; ler ++)
  {
    nota = 0;
    char prova[questoes];
    getchar();
    scanf("%s", prova);
    for (corrige = 0; corrige < questoes; corrige ++)
    {
      if (prova[corrige] == gabarito[corrige])
      {
        nota ++;
      }
    }
    printf("%d\n", nota);
  }
  return(0);
}
