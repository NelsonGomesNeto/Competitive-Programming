#include <stdio.h>

int conta, max, dinheiros, itens;

void bt(int a[], int i, int money, int buy)
{
  if (i == itens)
  {
    if (buy >= max && money <= dinheiros)
    {
      conta ++;
    }
    return;
  }
  if (money > dinheiros)
  {
    bt(a, i + 1, money, buy);
    return;
  }
  bt(a, i + 1, money + a[i], buy + 1);
  bt(a, i + 1, money, buy);
}

int main()
{
  int testes, run; scanf("%d", &testes);
  for (run = 0; run < testes; run ++)
  {
    scanf("%d", &itens);
    int m[itens], ler;
    for (ler = 0; ler < itens; ler ++)
    {
      scanf("%d", &m[ler]);
    }
    scanf("%d %d", &max, &dinheiros);
    conta = 0;
    bt(m, 0, 0, 0);
    printf("caso %d: %d\n", run, conta);
  }
  return(0);
}
