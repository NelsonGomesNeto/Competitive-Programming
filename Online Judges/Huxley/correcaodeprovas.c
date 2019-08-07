#include <stdio.h>
#include <string.h>

int main()
{
  int codigo, check, checkF, alunos = 0;
  float frequencia[99], nota = 0, percent = 0;
  float notaFre, most = 0, notaMost;
  char provaMestre[10], prova[10];
  scanf("%s", &*provaMestre);
  while (scanf("%d", &codigo) && codigo != 9999)
  {
    getchar();
    scanf("%[^\n]", &*prova);
    nota = 0; alunos ++;
    for (check = 0; check < 10; check ++)
    {
      if (prova[check] == provaMestre[check])
      {
        nota ++;
      }
    }
    frequencia[codigo - 1] = nota;
    if (nota >= 6)
    {
      percent ++;
    }
    printf("%d %.1f\n", codigo, nota);
  }
  for (check = 0; check < alunos; check ++)
  {
    notaFre = 0;
    for (checkF = 0; checkF < alunos; checkF ++)
    {
      if (frequencia[check] == frequencia[checkF])
      {
        notaFre ++;
      }
    }
    if (notaFre > most)
    {
      most = notaFre;
      notaMost = frequencia[check];
    }
  }
  percent = 100 * (percent / alunos);
  printf("%.1f%%\n%.1f\n", percent, notaMost);
  return(0);
}
