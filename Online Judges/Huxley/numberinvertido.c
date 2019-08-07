#include <stdio.h>

int main()
{
  int num, unit, dec;
  scanf("%i", &num);
  unit = num % 10;
  dec = num / 10;
  if (unit > 0)
  {
    printf("%i%i\n", unit, dec);
  }
  else
  {
    printf("%i\n", dec);
  }
  return(0);
}
