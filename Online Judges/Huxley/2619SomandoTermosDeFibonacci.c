#include <stdio.h>

int main()
{
  int n; scanf("%d", &n);
  int fib[21], a = 1, b = 1, i;
  for (i = 0; i <= 20; i ++)
  {
    fib[i] = b;
    int aux = a;
    a = a + b;
    b = aux;
  }
  
  int sum = 0, x;
  while (n --)
  {
    scanf("%d", &x);
    sum += fib[x - 1];
  }
  printf("%d\n", sum);
  
  return 0;
}