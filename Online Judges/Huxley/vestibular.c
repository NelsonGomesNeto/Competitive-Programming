#include <stdio.h>

int main()
{
  int letras, repeat, acertou = 0; scanf("%d", &letras);
  char certo[letras + 10], candidato[letras + 10];
  scanf("%s%s", certo, candidato);
  //printf("%s ~ %s \n", certo, candidato);
  for (repeat = 0; repeat < letras; repeat ++)
  {
    if (candidato[repeat] == certo[repeat])
    {
      acertou ++;
    }
  }
  printf("%d\n", acertou);
  return(0);
}
