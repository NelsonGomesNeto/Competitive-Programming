#include <stdio.h>
#include <string.h>

struct aluno
{
  int matricula;
  char nome[99];
  double nota;
};

int main()
{
  int alunos; scanf("%d", &alunos);
  struct aluno a[alunos + 1];
  int ler; double media = 0;
  for (ler = 1; ler <= alunos; ler ++)
  {
    scanf("%d", &a[ler].matricula);
    getchar();
    scanf("%[^\n]", a[ler].nome);
    scanf("%lf", &a[ler].nota);
    media += a[ler].nota;
  }
  media /= alunos;
  int o, b;
  for (o = 1; o <= alunos; o ++)
  {
    for (b = o; b <= alunos; b ++)
    {
      if (a[o].nota > a[b].nota)
      {
        a[0] = a[o];
        a[o] = a[b];
        a[b] = a[0];
      }
      else if (a[o].nota == a[b].nota)
      {
        if (a[o].matricula > a[b].matricula)
        {
          a[0] = a[o];
          a[o] = a[b];
          a[b] = a[0];
        }
      }
    }
  }
  for (ler = 1; ler <= alunos; ler ++)
  {
    if (a[ler].nota > media)
    {
      printf("Matricula: %d Nome: %s Nota: %.1lf\n", a[ler].matricula, a[ler].nome, a[ler].nota);
    }
  }
  printf("Media = %.2lf\n", media);
  return(0);
}
