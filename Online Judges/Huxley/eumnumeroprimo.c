#include <stdio.h>
#include <math.h>

int main()
{
  int num, divi;
  while (scanf("%d", &num) && num != -1)
  {
    if (num == 0 || num == 1)
    {
      printf("0\n"); continue;
    }
    int raiz = sqrt(num), is = 1;
    for (divi = 2; divi <= raiz; divi ++)
    {
      if (num % divi == 0)
      {
        is = 0;
        break;
      }
    }
    printf("%d\n", is);
  }
  return(0);
}
