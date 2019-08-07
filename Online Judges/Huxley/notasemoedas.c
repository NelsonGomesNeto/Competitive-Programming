#include <stdio.h>

int main()
{
  float preco; int precoINT;
  int n10000 = 0, n5000 = 0, n2000 = 0, n1000 = 0, n500 = 0, n200 = 0;
  int n100 = 0, n50 = 0, n25 = 0, n10 = 0, n5 = 0, n1 = 0;
  scanf("%f", &preco);
  precoINT = preco * 100;
  if (precoINT % 10000 >= 0)
  {
    n10000 = precoINT / 10000;
    precoINT %= 10000;
  }
  if (precoINT % 5000 >= 0)
  {
    n5000 = precoINT / 5000;
    precoINT %= 5000;
  }
  if (precoINT % 2000 >= 0)
  {
    n2000 = precoINT / 2000;
    precoINT %= 2000;
  }
  if (precoINT % 1000 >= 0)
  {
    n1000 = precoINT / 1000;
    precoINT %= 1000;
  }
  if (precoINT % 500 >= 0)
  {
    n500 = precoINT / 500;
    precoINT %= 500;
  }
  if (precoINT % 200 >= 0)
  {
    n200 = precoINT / 200;
    precoINT %= 200;
  }
  if (precoINT % 100 >= 0)
  {
    n100 = precoINT / 100;
    precoINT %= 100;
  }
  if (precoINT % 50 >= 0)
  {
    n50 = precoINT / 50;
    precoINT %= 50;
  }
  if (precoINT % 25 >= 0)
  {
    n25 = precoINT / 25;
    precoINT %= 25;
  }
  if (precoINT % 10 >= 0)
  {
    n10 = precoINT / 10;
    precoINT %= 10;
  }
  if (precoINT % 5 >= 0)
  {
    n5 = precoINT / 5;
    precoINT %= 5;
  }
  n1 = precoINT;

  printf("NOTAS:\n");
  printf("%d nota(s) de R$ 100.00\n", n10000);
  printf("%d nota(s) de R$ 50.00\n", n5000);
  printf("%d nota(s) de R$ 20.00\n", n2000);
  printf("%d nota(s) de R$ 10.00\n", n1000);
  printf("%d nota(s) de R$ 5.00\n", n500);
  printf("%d nota(s) de R$ 2.00\n", n200);
  printf("MOEDAS:\n");
  printf("%d moeda(s) de R$ 1.00\n", n100);
  printf("%d moeda(s) de R$ 0.50\n", n50);
  printf("%d moeda(s) de R$ 0.25\n", n25);
  printf("%d moeda(s) de R$ 0.10\n", n10);
  printf("%d moeda(s) de R$ 0.05\n", n5);
  printf("%d moeda(s) de R$ 0.01\n", n1);
  return(0);
}
