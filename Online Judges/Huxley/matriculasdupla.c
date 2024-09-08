#include <stdio.h>

int main()
{
  int alunosP2[45], alunosP3[30], ler, check;
  for (ler = 0; ler < 45; ler ++)
  {
    scanf("%d", &alunosP2[ler]);
  }
  for (ler = 0; ler < 30; ler ++)
  {
    scanf("%d", &alunosP3[ler]);
  }
  for (ler = 0; ler < 45; ler ++)
  {
    for (check = 0; check < 30; check ++)
    {
      if (alunosP2[ler] == alunosP3[check])
      {
        printf("%d ", alunosP2[ler]);
      }
    }
  }
  printf("\n");
  return(0);
}
