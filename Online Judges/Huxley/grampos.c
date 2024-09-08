#include <stdio.h>

int main()
{
  int alunos, grampos = 0, caixas, repeat;
  for (repeat = 0; repeat < 7; repeat ++)
  {
    scanf("%i", &alunos);
    grampos += alunos * 4;
  }
  caixas = grampos / 30;
  if (grampos % 30 != 0)
  { caixas ++; }
  printf("%i\n%i\n", grampos, caixas);
  return(0);
}
