#include <stdio.h>

int conta, max, dinheiros, itens, last, unik[9999], posi;

void bt(int a[], int i, int money, int buy)
{
  if (buy >= max && money <= dinheiros)
  {
    int j; int nope = 0;
    for (j = 0; j < posi; j ++)
    {
      if (money == unik[j])
      {
        nope ++;
      }
    }
    if (nope == 0)
    {
      unik[posi] = money;
      posi ++;
      conta += 1;
    }
  }
  if (i >= itens || money > dinheiros)
  {
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
      unik[ler] = -1;
      scanf("%d", &m[ler]);
    }
    scanf("%d %d", &max, &dinheiros);
    conta = 0; posi = 0;

    /*int o, b, aux;
    for (o = 0; o < itens; o ++)
    {
      for (b = o; b < itens; b ++)
      {
        if (m[o] < m[b])
        {
          aux = m[o];
          m[o] = m[b];
          m[b] = aux;
        }
      }
    }*/
    bt(m, 0, 0, 0);
    printf("caso %d: %d\n", run, conta);
  }
  return(0);
}
