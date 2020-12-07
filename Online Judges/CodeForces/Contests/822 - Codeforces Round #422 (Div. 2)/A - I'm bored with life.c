#include <stdio.h>

int min(int a, int b)
{
  return(a > b ? b : a);
}

int fact(int n)
{
  int f = 1;
  while (n > 0)
    f *= n --;

  return(f);
}

int main()
{
  int a, b;
  scanf("%d %d", &a, &b);

  printf("%d\n", fact(min(a, b)));

  return(0);
}
