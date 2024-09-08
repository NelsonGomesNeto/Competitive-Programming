#include <stdio.h>

struct aluno
{
  int ID; double nota;
  char nome[30];
};

int main()
{
  int alunos, i; scanf("%d", &alunos);
  struct aluno a[alunos + 1]; double media = 0;
  for (i = 0; i < alunos; i ++)
  {
    scanf("%d-%[^-]-%lf", &a[i].ID, a[i].nome, &a[i].nota);
    media += a[i].nota;
  } media /= alunos;
  int o, b;
  for (o = 0; o < alunos; o ++)
  {
    for (b = o; b < alunos; b ++)
    {
      if (a[o].nota > a[b].nota)
      {
        a[alunos] = a[o];
        a[o] = a[b];
        a[b] = a[alunos];
      }
      else if (a[o].nota == a[b].nota)
      {
        if (a[o].ID > a[b].ID)
        {
          a[alunos] = a[o];
          a[o] = a[b];
          a[b] = a[alunos];
        }
      }
    }
  }
  printf("Alunos abaixo da media:\n");
  int acimaDaMedia = 0;
  for (i = 0; i < alunos; i ++)
  {
    if (acimaDaMedia == 0 && a[i].nota >= media)
    {
      acimaDaMedia ++;
      printf("Alunos iguais ou acima da media:\n");
    }
    printf("Matricula: %d Nome: %s Nota: %.1lf\n", a[i].ID, a[i].nome, a[i].nota);
  }
  printf("Media = %.2lf\n", media);
  return(0);
}
