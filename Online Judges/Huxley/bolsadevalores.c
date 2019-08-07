#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define memCard pd[notAble][i]

int acoes, custo;

int max(int a, int b)
{
  return(a > b ? a : b);
}

int dp(int pd[][acoes], int ac[], int i, int notAble)
{
  if (i == acoes)
  {
    return(0);
  }
  if (memCard == -1)
  {
    int aux;
    memCard = dp(pd, ac, i + 1, notAble); //Não faz nada
    if (notAble == 0)
    {
      aux = dp(pd, ac, i + 1, 1) - ac[i] - custo; //Compra a ação
      memCard = max(memCard, aux); //Escolhe o melhor
    }
    if (notAble == 1)
    {
      aux = dp(pd, ac, i + 1, 0) + ac[i]; //Vende a ação
      memCard = max(memCard, aux); //Escolhe o melhor
    }
  }
  return(memCard); //Retorna o valor máximo
}

int main()
{
  scanf("%d %d", &acoes, &custo);

  int i, acao[acoes], DP[2][acoes];
  memset(DP[0], -1, acoes * sizeof(int)); //Setting the DP up
  memset(DP[1], -1, acoes * sizeof(int)); //Setting the DP up

  for (i = 0; i < acoes; i ++)
    scanf("%d", &acao[i]);

  int ans = dp(DP, acao, 0, 0);
  printf("%d\n", ans);
  return(0);
}
