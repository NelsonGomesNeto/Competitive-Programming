#include <stdio.h>
#include <string.h>

struct aluno
{
  char codigo_alu[40], nome_alu[510], sexo;
  int idade; float nota;
};

struct disciplina
{
  char codigo_dis[35], nome_dis[110];
  int matriculados; char dis[999999];
};

int main()
{
  int alunos, ler, masculino = 0, feminino = 0; scanf("%d", &alunos);
  struct aluno a[alunos];
  float mediaIdade = 0, divi = 0, mediaIdadeMaior = 0, diviMaior = 0;
  for (ler = 0; ler < alunos; ler ++)
  {
    getchar();
    scanf("%[^\n]", a[ler].codigo_alu);
    getchar();
    scanf("%[^\n]", a[ler].nome_alu);
    scanf("%d\n%c\n%f", &a[ler].idade, &a[ler].sexo, &a[ler].nota);
    if (a[ler].sexo == '1')
    { masculino ++; }
    else
    { feminino ++; }
    mediaIdade += a[ler].idade; divi ++;
    if (a[ler].nota > 7.5)
    {
      mediaIdadeMaior += a[ler].idade;
      diviMaior ++;
    }
  }
  mediaIdade /= divi;
  mediaIdadeMaior /= diviMaior;
  int disciplinas; scanf("%d", &disciplinas);
  struct disciplina d[disciplinas];
  for (ler = 0; ler < disciplinas; ler ++)
  {
    //printf("Bug\n");
    getchar();
    scanf("%[^\n]", d[ler].codigo_dis);
    getchar();
    scanf("%[^\n]", d[ler].nome_dis);
    //strcpy(d[ler].dis,'*');
    d[ler].matriculados = 0;
  }
  int matriculas, se, o, b, auxI; scanf("%d", &matriculas);
  char codNome[40], codDis[40];
  for (ler = 0; ler < matriculas; ler ++)
  {
    getchar();
    scanf("%s", codNome);
    getchar();
    scanf("%s", codDis);
    //printf("**********888\n");
    for (se = 0; se < alunos; se ++)
    {
      if (strcmp(codNome, a[se].codigo_alu) == 0)
      {
        for (o = 0; o < disciplinas; o ++)
        {
          //printf("~~~~~%sx%s\n", a[se].codigo_alu, codNome);
          if (strcmp(codDis, d[o].codigo_dis) == 0)
          {
            strcat(d[o].dis, a[se].nome_alu);
            strcat(d[o].dis, "*");
            d[o].matriculados += 1;
            break;
          }
        }
      }
    }
  }
  printf("%d\n%d\n", masculino, feminino);
  printf("%.2f\n%.2f\n", mediaIdade, mediaIdadeMaior);
  char aux[999999];
  for (o = 0; o < disciplinas; o ++)
  {
    for (b = o; b < disciplinas; b ++)
    {
      if (strcmp(d[o].nome_dis, d[b].nome_dis) > 0)
      {
        strcpy(aux, d[o].codigo_dis);
        strcpy(d[o].codigo_dis, d[b].codigo_dis);
        strcpy(d[b].codigo_dis,aux);

        strcpy(aux, d[o].nome_dis);
        strcpy(d[o].nome_dis, d[b].nome_dis);
        strcpy(d[b].nome_dis,aux);

        strcpy(aux, d[o].dis);
        strcpy(d[o].dis, d[b].dis);
        strcpy(d[b].dis,aux);

        auxI = d[o].matriculados;
        d[o].matriculados = d[b].matriculados;
        d[b].matriculados = auxI;
      }
    }
  }
  for (o = 0; o < disciplinas; o ++)
  {
    printf("%s\n", d[o].nome_dis);
    printf("%d\n", d[o].matriculados);
    if (d[o].matriculados != 0)
    {
      char alu[999][510]; int j, i, iM;
      iM = 0;
      for (j = 0; j < d[o].matriculados; j ++)
      {
        i = 0;
        while (d[o].dis[iM] != '*' && d[o].dis[iM] != '\0')
        {
          alu[j][i] = d[o].dis[iM];
          i ++; iM ++;
        }
        iM ++;
      }
      for (i = 0; i < d[o].matriculados; i ++)
      {
        for (j = i; j < d[o].matriculados; j ++)
        {
          if (strcmp(alu[i], alu[j]) > 0)
          {
            strcpy(aux, alu[i]);
            strcpy(alu[i], alu[j]);
            strcpy(alu[j], aux);
          }
        }
      }
      for (i = 0; i < d[o].matriculados; i ++)
      {
        printf("%s\n", alu[i]);
      }
      for (i = 0; i < d[o].matriculados; i ++)
      {
        for (j = 0; j < 510; j ++)
        {
          alu[i][j] = '\0';
        }
      }
    }
  }
  return(0);
}
