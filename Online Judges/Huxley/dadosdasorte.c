#include <stdio.h>

int vezes, li;

void check(int soma, int i, int fim, int wanted)
{
  if (i == fim || soma + ((fim - i) * 6) < wanted)
  {
    if (soma >= wanted)
    {
      vezes ++;
    }
    return;
  }
  int lado;
  for (lado = 6; lado > 0; lado --)
  {
    check(soma + lado, i + 1, fim, wanted);
  }
}

int main()
{
  int dados, casas;
  scanf("%d %d", &dados, &casas);
  check(0, 0, dados, casas);
  printf("%d\n", vezes);
  return(0);
}
