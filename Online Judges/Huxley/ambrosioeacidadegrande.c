#include <stdio.h>

void corrige(int *onibus, int tot)
{
  int aux = *onibus;
  while (*onibus < tot)
  {
    *onibus += aux;
  }
}

int main()
{
  int locais, ler, aux; scanf("%d", &locais);
  int tempo[locais + 10], oni[locais + 10], total = 0;
  for (ler = 0; ler < locais; ler ++)
  {
    scanf("%d", &tempo[ler]);
  }
  for (ler = 0; ler < locais; ler ++)
  {
    scanf("%d", &oni[ler]);
  }
  total += tempo[0];
  for (ler = 1; ler < locais; ler ++)
  {
    corrige(&oni[ler], total);
    total += ((oni[ler] - total) + tempo[ler]);
  }
  printf("%d\n", total);
  return(0);
}
