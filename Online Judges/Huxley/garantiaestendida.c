#include <stdio.h>

int main()
{
  float preco;
  int garantia;
  scanf("%f\n%i", &preco, &garantia);
  if (garantia == 0)
  {
    printf("%.2f\n", preco);
  }
  else if (garantia > 1)
  {
    preco *= 1.05;
    printf("%.2f\n", preco);
  }
  else
  {
    preco *= 1.03;
    printf("%.2f\n", preco);
  }
  return(0);
}
