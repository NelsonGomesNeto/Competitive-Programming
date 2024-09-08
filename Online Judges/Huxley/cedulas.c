#include <stdio.h>

int main()
{
  int preco, precoBack, n100 = 0, n50 = 0;
  int n20 = 0, n10 = 0, n5 = 0, n2 = 0, n1 = 0;
  scanf("%i", &preco);
  precoBack = preco;
  while (preco >= 100)
  {
    preco -= 100;
    n100 ++;
  }
  while (preco >= 50)
  {
    preco -= 50;
    n50 ++;
  }
  while (preco >= 20)
  {
    preco -= 20;
    n20 ++;
  }
  while (preco >= 10)
  {
    preco -= 10;
    n10 ++;
  }
  while (preco >= 5)
  {
    preco -= 5;
    n5 ++;
  }
  while (preco >= 2)
  {
    preco -= 2;
    n2 ++;
  }
  while (preco >= 1)
  {
    preco -= 1;
    n1 ++;
  }
  printf("%i\n%i nota(s) de R$ 100,00\n", precoBack, n100);
  printf("%i nota(s) de R$ 50,00\n", n50);
  printf("%i nota(s) de R$ 20,00\n", n20);
  printf("%i nota(s) de R$ 10,00\n", n10);
  printf("%i nota(s) de R$ 5,00\n", n5);
  printf("%i nota(s) de R$ 2,00\n", n2);
  printf("%i nota(s) de R$ 1,00\n", n1);
  return(0);
}
