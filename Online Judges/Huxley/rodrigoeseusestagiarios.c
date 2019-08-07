#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int testes; long int num; scanf("%d", &testes);
  while (testes > 0)
  {
    scanf("%ld", &num);
    long int i; int divi = 2, no = 0;
    for (i = 2; i < sqrt(num); i ++)
    {
      if (num % i == 0)
      {
        divi ++;
        break;
      }
    }
    if (divi == 3)
    {
      for (; i <= num / 2; i ++)
      {
        if (num % i == 0)
        {
          printf("YES\n");
          no ++;
          break;
        }
      }
    }
    if (no == 0)
    {
      printf("NO\n");
    }
    testes --;
  }
  return(0);
}
