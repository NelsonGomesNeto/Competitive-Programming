#include <stdio.h>

int main()
{
  int codigo, caroCodigo, quanti, caroQuanti; float preco, caro = 0;
  while (scanf("%d %d %f", &codigo, &quanti, &preco) && !(codigo == 0 && quanti == 0 && preco == 0))
  {
    if (quanti * preco > caro)
    {
      caro = quanti * preco;
      caroCodigo = codigo;
      caroQuanti = quanti;
    }
  }
  if (caro > 0)
  {
    printf("Item mais caro\n");
    printf("Codigo: %d\n", caroCodigo);
    printf("Quantidade: %d\n", caroQuanti);
    printf("Custo: %.2f\n", caro);
  }
  else
  {
    printf("nao tem compras\n");
  }
  return(0);
}
