#include <stdio.h>

int fatorial(int a)
{
  if (a < 1)
  {
    return(1);
  }
  a *= fatorial(a - 1);
  return(a);
}

int main()
{
  int num;
  printf("Digite um numero inteiro:\n");
  scanf("%d", &num);
  num = fatorial(num);
  printf("Fatorial: %d\n", num);
}
