#include <stdio.h>

struct item
{
  int ID; char nome[99]; float preco;
};

int main()
{
  int itens; scanf("%d", &itens);
  struct item i[itens]; int ler;
  for (ler = 0; ler < itens; ler ++)
  {
    scanf("%d", &i[ler].ID);
    getchar(); scanf("%[^\n]", i[ler].nome);
    scanf("%f", &i[ler].preco);
  }
  int pedido; float pagar = 0;
  while (scanf("%d", &pedido) && pedido != 0)
  {
    int quanti, search; float atual = 0;
    for (search = 0; search < itens; search ++)
    {
      if (pedido == (int) i[search].ID)
      {
        atual += i[search].preco;
        break;
      }
    }
    /*if (atual == 0)
    {
      break;
    }*/
    scanf("%d", &quanti);
    if (quanti > 0)
    {
      pagar += (atual * quanti);
    }
  }
  printf("%.2f\n", pagar);
  return(0);
}
