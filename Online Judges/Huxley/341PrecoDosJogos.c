#include <stdio.h>
double discount[6] = {0.25, 0.2, 0.18, 0.15, 0.12, 0.10};

double calc(double price, int dif)
{
  if (price <= 45) return(price);
  int i;
  for (i = 0; i < 3; i ++)
  {
    price *= (1 - (discount[dif] / (1 + (price <= 100))));
    if (price <= 45) return(45);
  }
  return(price);
}

int main()
{
  int q, i; scanf("%d", &q);
  for (i = 0; i < q; i ++)
  {
    int dif; double price; scanf("%d %lf", &dif, &price);
    printf("Jogo[%d] = R$%.2lf\n", i, calc(price, dif));
  }
  return(0);
}
