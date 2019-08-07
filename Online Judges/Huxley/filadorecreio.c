#include <stdio.h>

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int alunos; scanf("%d", &alunos);
    int nota[alunos], backUp[alunos], ler, o, b, aux, still = 0;
    for (ler = 0; ler < alunos; ler ++)
    {
      scanf("%d", &nota[ler]);
      backUp[ler] = nota[ler];
    }
    for (o = 0; o < alunos - 1; o ++)
    {
      for (b = o; b < alunos; b ++)
      {
        if (nota[b] > nota[o])
        {
          aux = nota[o];
          nota[o] = nota[b];
          nota[b] = aux;
        }
      }
    }
    for (ler = 0; ler < alunos; ler ++)
    {
      if (nota[ler] == backUp[ler])
      {
        still ++;
      }
    }
    printf("%d\n", still);
    testes --;
  }
}
