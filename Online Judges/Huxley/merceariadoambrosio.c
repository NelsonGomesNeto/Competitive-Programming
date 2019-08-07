#include <stdio.h>

int main()
{
  int ID, quanti; float preco;
  scanf("%d\n%d", &ID, &quanti);
  if (ID == 1)
  {
    preco = (5.3 * quanti);
  }
  else if (ID == 2)
  {
    preco = (6 * quanti);
  }
  else if (ID == 3)
  {
    preco = (3.2 * quanti);
  }
  else
  {
    preco = (2.5 * quanti);
  }
  if (quanti >= 15 || preco >= 40)
  {
    preco *= 0.85;
  }
  printf("R$ %.2f\n", preco);
  return(0);
}
