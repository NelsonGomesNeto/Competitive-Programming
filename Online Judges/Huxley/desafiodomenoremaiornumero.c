#include <stdio.h>

int main()
{
  int num, maior = 0, menor = 10001;
  while (scanf("%d", &num) && num != 0)
  {
    if (num > maior)
    {
      maior = num;
    }
    if (num < menor)
    {
      menor = num;
    }
  }
  printf("%d %d\n", menor, maior);
}
