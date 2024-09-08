#include <stdio.h>

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int soma = 0, amigos, quantia, repeat, check;
    scanf("%d %d", &amigos, &quantia);
    int preco[amigos];
    for (repeat = 0; repeat < amigos; repeat ++)
    {
      scanf("%d", &preco[repeat]);
    }
    for (repeat = 0; repeat < amigos; repeat ++)
    {
      soma = 0;
      for (check = repeat; check < amigos; check ++)
      {
        soma += preco[check];
        if (soma == quantia)
        {
          repeat = amigos; check = amigos;
          printf("YES\n");
          break;
        }
      }
    }
    if (repeat == amigos && check == amigos)
    {
      printf("NO\n");
    }
    testes --;
  }
  return(0);
}
