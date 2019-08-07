#include <stdio.h>
#include <math.h>

int main()
{
  int num, primo, prox, out = 0, power;
  scanf("%d", &num);
  primo = 2;
  while (num > 1)
  {
    power = 1;
    out ++;
    if (primo > num)
    {
      primo = 2;
    }
    if (primo == num)
    {
      printf("%d**1\n", primo);
      num /= primo;
    }
    while (num % (int) pow(primo,power) == 0)
    {
      power ++;
    }
    power --;
    if (num % (int) pow(primo, power) == 0 && power >= 1)
    {
      num /= pow(primo,power);
      printf("%d**%d\n", primo, power);
    }
    prox = primo + 1;
    for (primo = 2; primo < sqrt(prox) + 1; primo ++)
    {
      if (prox % primo == 0)
      {
        prox ++; primo = 2;
      }
    }
    //printf("%d\n", num);
    primo = prox;
  }
  return(0);
}
