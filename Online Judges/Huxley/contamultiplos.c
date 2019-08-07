#include <stdio.h>

int main()
{
  int num1, num2, repeat = 1, multiplos = 0;
  scanf("%i\n%i", &num1, &num2);
  while (repeat < 50)
  {
    if (repeat % num1 == 0)
    {
      if (repeat % num2 == 0)
      {
        multiplos ++;
      }
    }
    repeat ++;
  }
  printf("%i\n", multiplos);
  return(0);
}
