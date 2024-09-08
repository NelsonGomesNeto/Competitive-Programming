#include <stdio.h>

int main()
{
  int n, altura, base; scanf("%d", &n);
  for (altura = 1; altura <= n; altura ++)
  {
    for (base = 1; base <= altura; base ++)
    {
      printf("*");
    }
    printf("\n");
  }
  return(0);
}
