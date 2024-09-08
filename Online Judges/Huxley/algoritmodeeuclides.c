#include <stdio.h>

int MDC(int n1, int n2)
{
  if (n1 % n2 == 0)
  {
    return(n2);
  }
  MDC(n2, n1 % n2);
}

int main()
{
  int testes, num1, num2; scanf("%d", &testes);
  while (testes > 0)
  {
    scanf("%d %d", &num1, &num2);
    printf("MDC(%d,%d) = %d\n", num1, num2, MDC(num1,num2));
    testes --;
  }
  return(0);
}
