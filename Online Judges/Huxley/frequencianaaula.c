#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int reg, aluno[100000], i, ultimo = 0;
  scanf("%d", &reg);
  memset(aluno, 0, 100000);
  int ler, presentes = 0;
  for (ler = 0; ler < reg; ler ++)
  {
    int num; scanf("%d", &num);
    int no = 0;
    for (i = 0; i < ultimo; i ++)
    {
      if (aluno[i] == num)
      {
        no ++;
        break;
      }
    }
    aluno[ultimo] = num;
    ultimo ++;
    if (no == 0)
    {
      presentes ++;
    }
  }
  /*for (ler = 0; ler < reg; ler ++)
  {
    int num; scanf("%d", &num);
    if (num == 1000000)
    {
      if (ultimo == 0)
      {
        presentes ++;
      }
      ultimo = 1;
    }
    else
    {
      if (aluno[num] == 0)
      {
        presentes ++;
      }
      aluno[num] = 1;
    }
  }*/
  printf("%d\n", presentes);
  return(0);
}
