#include <stdio.h>
#include <string.h>

int main()
{
  int repeat, check, winner, alunos;
  char nome[alunos][30], aux[30];
  scanf("%d %d", &alunos, &winner);
  for (repeat = 0; repeat < alunos; repeat ++)
  {
    getchar();
    scanf("%[^\n]", nome[repeat]);
  }
  for (repeat = 0; repeat < alunos; repeat ++)
  {
    for (check = 0; check < alunos; check ++)
    {
      if (strcmp(nome[repeat],nome[check]) < 0)
      {
        strcpy(aux,nome[repeat]);
        strcpy(nome[repeat],nome[check]);
        strcpy(nome[check],aux);
      }
    }
  }
  printf("%s\n", nome[winner - 1]);
  return(0);
}
