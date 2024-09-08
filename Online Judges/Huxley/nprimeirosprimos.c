#include <stdio.h>
#include <math.h>

int main()
{
  int primeiros, printar = 0, primos, nao = 1, num = 3; scanf("%d", &primeiros);
  while (printar < primeiros)
  {
    nao = 1;
    if (printar == 0 && num == 3)
    {
      printf("2\n");
      printar ++;
    }
    else
    {
      if (num % 2 != 0)
      {
        for (primos = 2; primos <= ceil(sqrt(num)); primos ++)
        {
          if (num % primos == 0)
          {
            nao = 0;
            break;
          }
        }
        if (nao == 1)
        {
          printf("%d\n", num);
          printar ++;
        }
      }
    }
    if (primeiros >= 2 && printar < 2)
    {
      printf("3\n");
      printar ++;
    }
    num ++;
  }
  return(0);
}
