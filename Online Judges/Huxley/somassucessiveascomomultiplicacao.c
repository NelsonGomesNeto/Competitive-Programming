#include <stdio.h>

int once = 0, soma = 0;
int mult(int n, int m)
{
  /*if (n < 0 && m < 0 && once == 0)
  {
    once ++;
    n *= -1;
  }*/
  if (m > 0)
  {
    soma += n;
    mult(n, m - 1);
  }
  else if (m < 0)
  {
    soma -= n;
    mult(n, m + 1);
  }
  return(soma);
}

int main()
{
  int a, b; scanf("%d\n%d", &a, &b);
  printf("%d\n", mult(a,b));
  return(0);
}
