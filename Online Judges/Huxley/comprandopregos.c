#include <stdio.h>

int main()
{
  int pregos, total = 0, resto; float preco;
  while (scanf("%d", &pregos) && pregos % 2 == 0)
  {
    total += pregos;
  }
  if (total >= 12)
  {
    if (total % 12 == 0)
    {
      total /= 12;
    }
    else
    {
      total = (total / 12) + 1;
    }
    preco = (total) * 7.89;
    resto = ((total % 12));
  }
  else
  {
    preco = 7.89;
    resto = 12 - total;
  }
  printf("%.2f\n%d\n", preco, resto);
}
